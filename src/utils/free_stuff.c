/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 22:25:56 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/24 17:58:20 by amouhand         ###   ########.fr       */
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
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	*head = NULL;
}

void	free_char_array(char **array)
{
	int i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
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
			if (root->left->cmd)
			{
				free_cmd(root->left->cmd);
				root->left->cmd = NULL;
			}
		}
		else
			free_tree(root->left->pipe);
		free(root->left);
		root->left = NULL;
	}
	free(root);
	root = NULL;
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;

	if (cmd->args)
		free_char_array(cmd->args);
	if (cmd->redirections)
		free_redirections(cmd->redirections);
	free(cmd);
	cmd = NULL;
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

void free_parser(t_parser *parser)
{
	if (parser)
	{
		if (parser->prompt)
			free(parser->prompt);
		if (parser->line)
			free(parser->line);
		if (parser->result)
			free_char_array(parser->result);
		if (parser->head)
			free_tokens(&parser->head);
		if (parser->cmd)
			free(parser->cmd);
		if (parser->root)
			free_tree(parser->root);
		free(parser);
	}
}
