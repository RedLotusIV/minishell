/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:29:40 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/13 19:40:46 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

// void	allocate_cmd(t_cmd *cmd, t_token *token)
// {
	// i should count how many commands i have in the tokens, meaning the number of pipes + 1
	// i should allocate the number of commands i have
	// i should then link the commands together as a doubly linked list
	// i should then allocate the number of arguments i have in each command as a char **
	// so in the end i should have a doubly linked list of commands, each command has a char ** of arguments and a t_token of redirections
	// which will make it so easy to be executed in the execution part, with pipes and redirections and everything
// }
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
	cmd = malloc(sizeof(t_cmd) * (count + 2));
	if (!cmd)
		return (NULL);
	allocate_cmd(cmd, head);
	tmp = cmd;
	for (int i = 0 ; i < count ; i++)
	{
		for (int j = 0 ; tmp[i]->args[j] ; j++)
			printf("%s\n", tmp[i]->args[j]);
		if (tmp[i]->redir)
		{
			printf("%s\n", tmp[i]->redir->redir->value);
			printf("%s\n", tmp[i]->redir->arg);
		}
	}
	return (cmd);
}
void	allocate_cmd(t_cmd **cmd, t_token *head)
{
	int i;
	t_token	*current;
	t_token	*before;
	t_token *redirect;
	t_token *file;
	int flag;
	int count;
	
	i = 0;
	current = head;
	before = head;
	while (current)
	{
		while (current && current->type != PIPE)
		{
			count = 0;
			flag = 0;
			if (current->type == WORD && before->type != REDIR && before->type != PIPE
				&& before->type != INPUT && before->type != APPEND && before->type != HEREDOC)
			{
				count++;
				before = current;
				current = current->next;
			}
			else if (current->type == WORD && before->type != WORD && before->type != PIPE)
			{
				redirect = before;
				before = current;
				file = current;
				current = current->next;
				flag = 1;
			}
		}
		if (current && current->type == PIPE)
		{
			before = current;
			current = current->next;
		}
		else if (!current)
			break ;
		cmd[i]->args = malloc(sizeof(char *) * (count + 1));
		if (!cmd[i] || !cmd[i]->args)
			return ;
		cmd[i]->args[count] = NULL;
		if (flag == 1)
			cmd[i]->redir = malloc(sizeof(t_redirection));
		else
			cmd[i]->redir = NULL;
		if (!cmd[i] || !cmd[i]->redir)
			return ;
		cmd[i]->redir->redir = redirect;
		cmd[i]->redir->arg = file->value;
		i++;
	}
}