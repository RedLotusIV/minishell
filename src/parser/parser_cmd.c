/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:29:40 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/15 21:31:00 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

// void	allocate_cmd(t_cmd *cmd, t_token *token)
// {
	// i should count how many commands i have in the tokens, meaning the number of pipes + 1
	// i should allocate the number of commands i have
	// i should then allocate the number of arguments i have in each command as a char **
	// so in the end i should have an array of commands, each command has a char ** of arguments and a t_token of redirections
	// which will make it so easy to be executed in the execution part, with pipes and redirections and everything
// }ex
t_cmd	**parse_cmd(t_token *head)
{
	t_cmd	**cmd;
	t_token *token_tmp;
	t_cmd **tmp;
	int i;
	int count;

	i = 0;
	count = 0;
	token_tmp = head;
	while (token_tmp)
	{
		if (token_tmp->type == PIPE)
			count++;
		token_tmp = token_tmp->next;
	}
	cmd = malloc(sizeof(t_cmd *) * (count + 2));
	if (!cmd)
		return (NULL);
	allocate_cmd(cmd, head);
	tmp = cmd;
	for (int i = 0 ; tmp[i] ; i++)
	{
		for (int j = 0 ; tmp[i]->args[j] ; j++)
			printf("arg[%d] : %s at command %d\n", j + 1, tmp[i]->args[j], i + 1);
		if (tmp[i]->redirections)
		{
			printf("redir   : %s at command %d\n", tmp[i]->redirections->redir->value, i + 1);
			printf("file    : %s at command %d\n", tmp[i]->redirections->arg, i + 1);
			tmp[i]->redirections = tmp[i]->redirections->next;
		}
	}
	return (cmd);
}
void	allocate_cmd(t_cmd **cmd, t_token *head)
{
	int i;
	int j;
	t_token	*current;
	t_token	*before;
	t_token *redirect;
	t_token *file;
	t_cmd	*tmp;
	t_token *tmp_token;
	t_token *before_tmp;
	int flag;
	int count;
	
	i = 0;
	current = head;
	before = head;
	while (current)
	{
		count = 0;
		flag = 0;
		tmp_token = current;
		cmd[i] = malloc(sizeof(t_cmd));
		if (!cmd[i])
			return ;
		while (current && current->type != PIPE)
		{
			if (current->type == WORD && before->type != REDIR && before->type != PIPE
				&& before->type != INPUT && before->type != APPEND && before->type != HEREDOC)
			{
				count++;
				before = current;
				current = current->next;
			}
			else if (current->type == REDIR || current->type == PIPE || current->type == INPUT 
			|| current->type == APPEND || current->type == HEREDOC)
			{
				redirect = current;
				before = current;
				current = current->next;
				if (current->type == WORD)
					add_redirection(cmd[i], redirect, current->value);
			}
			else
			{
				before = current;
				current = current->next;
			}
		}
		cmd[i]->args = malloc(sizeof(char *) * (count + 1));
		if (!cmd[i]->args)
			return ;
		tmp = cmd[i];
		before_tmp = tmp_token;
		j = 0;
		while(tmp_token && tmp_token->type != PIPE)
		{
			if (tmp_token->type == WORD && (before_tmp->type != REDIR && before_tmp->type != PIPE
				&& before_tmp->type != INPUT && before_tmp->type != APPEND && before_tmp->type != HEREDOC))
			{
				tmp->args[j] = ft_strdup(tmp_token->value);
				j++;
			}
			before_tmp = tmp_token;
			tmp_token = tmp_token->next;
		}
		tmp->args[j] = NULL;
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
    new_redir->redir = redir_token;
    new_redir->arg = strdup(arg);
    new_redir->next = NULL;
    if (cmd->redirections == NULL)
        cmd->redirections = new_redir;
	else 
	{
        current = cmd->redirections;
        while (current->next != NULL)
            current = current->next;
        current->next = new_redir;
    }
}