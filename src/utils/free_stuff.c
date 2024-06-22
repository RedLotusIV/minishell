/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 22:25:56 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/23 00:20:31 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

void	free_tokens(t_token **head)
{
	t_token *tmp;
	t_token *current;

	current = *head;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
	*head = NULL;
}

void	free_char_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

void	free_tree(t_pipe *root)
{
	if (!root)
		return;
	if (root->right)
	{
		free_cmd(root->right);
		root->right = NULL;
	}
	if (root->left)
	{
		if (root->left_type == PIPE_CMD)
		{
			if (root->left->cmd) {
				free_cmd(root->left->cmd);
				root->left->cmd = NULL;
			}
		}
		else
		{
			free_tree(root->left->pipe);
			root->left->pipe = NULL;
		}
	}
	free(root);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->args)
			free_char_array(cmd->args);
		if (cmd->redirections)
			free_redirections(cmd->redirections);
		free(cmd);
	}
}

void	free_redirections(t_redirection *redirections)
{
	t_redirection *tmp;

	while (redirections)
	{
		tmp = redirections;
		redirections = redirections->next;
		free(tmp->arg);
		free(tmp);
		tmp = NULL;
	}
	redirections = NULL;
}
void free_parser(t_parser *parser, t_pipe *root, char *prompt, char *cwd)
{
	if (cwd)
		free(cwd);
	if (prompt)
		free(prompt);
	if (root)
		free_tree(root);
	if (parser && parser->line)
		free(parser->line);
	if (parser && parser->result)
		free_char_array(parser->result);
	if (parser && parser->head)
		free_tokens(&parser->head);
	free(parser);
}