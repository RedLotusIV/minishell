/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:56:25 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/24 14:05:04 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	skip_quotes(char *command, int i)
{
	int	tmp;

	tmp = 0;
	while (command[i])
	{
		if (command[i] == '\"' || command[i] == '\'')
		{
			tmp = command[i];
			i++;
			while (command[i] && command[i] != tmp)
				i++;
			if (command[i] == tmp)
				i++;
		}
		while (command[i] && command[i] != '|' && command[i] != '<'
			&& command[i] != '>' && command[i] != ' ' && command[i] != '\t'
			&& command[i] != '\n' && command[i] != '\"' && command[i] != '\'')
			i++;
		if (command[i] != '\'' && command[i] != '\"')
			break ;
	}
	return (i);
}

int	skip_special_char(char *command, int i)
{
	if (command[i + 1] == command[i] && command[i] != '|')
		i += 2;
	else
		i++;
	return (i);
}

int	skip_everything_else(char *command, int i)
{
	int tmp;

	tmp = 0;
	while (command[i])
	{
		while (command[i] && command[i] != '|' && command[i] != '<'
			&& command[i] != '>' && command[i] != ' ' && command[i] != '\t'
			&& command[i] != '\n' && command[i] != '\"' && command[i] != '\'')
			i++;
		if (command[i] == '\"' || command[i] == '\'')
		{
			tmp = command[i];
			i++;
			while (command[i] && command[i] != tmp)
				i++;
			if (command[i] == tmp)
				i++;
		}
		if (command[i] == '|' || command[i] == '<'
			|| command[i] == '>' || command[i] == ' ' || command[i] == '\t'
			|| command[i] == '\n')
			break ;
	}
	return (i);
}

char	*copy_segment(char *command, int start, int end)
{
	int		l;
	char	*result;
	int		j;
	int		tmp;

	l = 0;
	result = malloc(end - start + 1);
	if (!result)
		return (NULL);
	j = start;
	while (j < end)
	{
		if (command[j] == '\"' || command[j] == '\'')
		{
			tmp = command[j++];
			while (command[j] && command[j] != tmp)
				result[l++] = command[j++];
			if (command[j] == tmp)
				j++;
		}
		else
			result[l++] = command[j++];
	}
	result[l] = '\0';
	return (result);
}

void	print_tree(t_pipe *root)
{
	if (root == NULL)
		return ;
	if (root->right && root->right->args && root->right->args[0])
		printf("right is a cmd: %s\n", root->right->args[0]);
	if (root->left_type == PIPE_CMD && root->left && root->left->cmd
		&& root->left->cmd->args && root->left->cmd->args[0])
		printf("left is a cmd: %s\n", root->left->cmd->args[0]);
	else if (root->left_type == PIPE_PIPE)
		printf("left is a Pipe\n");
	if (root->left_type == PIPE_PIPE && root->left && root->left->pipe)
		print_tree(root->left->pipe);
}
