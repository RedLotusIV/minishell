/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:29:40 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/16 10:28:15 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_cmd	**parse_cmd(t_token *head)
{
	t_cmd	**cmd;
	t_cmd **tmp;
	t_redirection *redirections;
	int i;
	int count;

	i = 0;
	count = 0;
	count = count_pipes(head);
	cmd = malloc(sizeof(t_cmd *) * (count + 2));
	if (!cmd)
		return (NULL);
	allocate_cmd(cmd, head);
	tmp = cmd;
	print_command_details(tmp);
	return (cmd);
}
void process_token(t_token **current, t_token **before, t_cmd **cmd, int i)
{
    t_token *redirect;
    while (*current && (*current)->type != PIPE) 
	{
        if ((*current)->type == WORD && (*before)->type != REDIR && (*before)->type != PIPE &&
            (*before)->type != INPUT && (*before)->type != APPEND && (*before)->type != HEREDOC)
		{
            *before = *current;
            *current = (*current)->next;
        }
		else if ((*current)->type == REDIR || (*current)->type == PIPE || (*current)->type == INPUT ||
                   (*current)->type == APPEND || (*current)->type == HEREDOC)
		{
            redirect = *current;
            *before = *current;
            *current = (*current)->next;
            if (*current && (*current)->type == WORD)
                add_redirection(cmd[i], redirect, (*current)->value);
        }
		else
		{
            *before = *current;
            *current = (*current)->next;
        }
    }
}

int count_args(t_token *start, t_token *end)
{
    int count;

	count = 0;
    while (start && start != end)
	{
        if (start->type == WORD && start->type != REDIR && start->type != PIPE &&
            start->type != INPUT && start->type != APPEND && start->type != HEREDOC)
            count++;
        start = start->next;
    }
    return (count);
}

void fill_args(t_token *start, t_token *end, t_cmd *cmd)
{
    int j;
    t_token *before_tmp;

	j = 0;
	before_tmp = start;
    while (start && start != end)
	{
        if (start->type == WORD && (before_tmp->type != REDIR && before_tmp->type != INPUT 
		&& before_tmp->type != APPEND && before_tmp->type != HEREDOC))
		{
            cmd->args[j] = ft_strdup(start->value);
            j++;
        }
        before_tmp = start;
        start = start->next;
    }
    cmd->args[j] = NULL;
}

void allocate_cmd(t_cmd **cmd, t_token *head)
{
    int i;
	int count;
    t_token *current;
    t_token *before;
	t_token *tmp_token;
    
	i = 0;
	current = head;
	before = head;
    while (current)
	{
        tmp_token = current;
        cmd[i] = malloc(sizeof(t_cmd));
        if (!cmd[i])
			return;
        process_token(&current, &before, cmd, i);
        int count = count_args(tmp_token, current);
        cmd[i]->args = malloc(sizeof(char *) * (count + 1));
        if (!cmd[i]->args)
			return;
        fill_args(tmp_token, current, cmd[i]);
        if (current && current->type == PIPE)
		{
            before = current;
            current = current->next;
        }
        i++;
    }
    cmd[i] = NULL;
}

void add_redirection(t_cmd *cmd, t_token *redir_token, char *arg)
{
	t_redirection *new_redir;
	t_redirection *current;

	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return ;
	new_redir->redir = redir_token;
	new_redir->arg = strdup(arg);
	new_redir->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else 
	{
		current = cmd->redirections;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}
int count_pipes(t_token *head)
{
    int count;
	t_token *tmp;

	count = 0;
	tmp = head;
    while (tmp)
	{
        if (tmp->type == PIPE)
			count++;
        tmp = tmp->next;
    }
    return count;
}
void print_command_details(t_cmd **cmd)
{
    t_redirection *redirections;
    for (int i = 0; cmd[i]; i++) {
        printf("+++++++++++++++ command [%d] +++++++++++++++\n", i + 1);
        for (int j = 0; cmd[i]->args[j]; j++)
            printf("arg[%d] : %s at command %d\n", j + 1, cmd[i]->args[j], i + 1);
        redirections = cmd[i]->redirections;
        while (redirections) {
            printf("redir   : %s at command %d\n", redirections->redir->value, i + 1);
            printf("file    : %s at command %d\n", redirections->arg, i + 1);
            redirections = redirections->next;
        }
    }
}