/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:29:40 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/18 13:38:28 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_cmd	**parse_cmd(t_token *head)
{
	t_cmd	**cmd;
	int		count;

	count = 0;
	count = count_pipes(head);
	cmd = malloc(sizeof(t_cmd *) * (count + 2));
	if (!cmd)
		return (NULL);
	allocate_cmd(cmd, head);
	return (cmd);
}

void	allocate_cmd(t_cmd **cmd, t_token *head)
{
	int		i;
	t_token	*current;
	t_token	*before;
	t_token	*tmp_token;

	i = 0;
	current = head;
	while (current)
	{
		tmp_token = current;
		initialize_cmd(cmd, tmp_token, i);
		process_token(&current, &before, cmd, i);
		if (current && current->type == PIPE)
		{
			before = current;
			current = current->next;
		}
		i++;
	}
	cmd[i] = NULL;
}

void	initialize_cmd(t_cmd **cmd, t_token *current, int i)
{
	t_token	*tmp_token;
	int		count;

	cmd[i] = malloc(sizeof(t_cmd));
	if (!cmd[i])
		return ;
	cmd[i]->redirections = NULL;
	tmp_token = current;
	count = count_args(tmp_token, NULL);
	cmd[i]->args = malloc(sizeof(char *) * (count + 1));
	if (!cmd[i]->args)
		return ;
	fill_args(tmp_token, NULL, cmd[i]);
}

void	add_redirection(t_cmd *cmd, t_token *redir_token, char *arg)
{
	t_redirection	*new_redir;
	t_redirection	*current;

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
