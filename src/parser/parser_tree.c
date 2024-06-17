/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:54:21 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/17 19:29:19 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_pipe	*assign_cmd_to_right(t_pipe *tmp_pipe, t_cmd **tmp, int *i)
{
	if (tmp[*i] && !tmp_pipe->right)
	{
		tmp_pipe->right = tmp[*i];
		tmp_pipe->left_type = PIPE_CMD;
		(*i)++;
	}
	return (tmp_pipe);
}

t_pipe	*assign_cmd_to_left(t_pipe *tmp_pipe, t_cmd **tmp, int *i, int *pipes)
{
	if (tmp[*i] && !tmp_pipe->left)
	{
		if (*pipes - 1)
		{
			tmp_pipe->left_type = PIPE_PIPE;
			tmp_pipe->left = malloc(sizeof(t_left));
			if (!tmp_pipe->left)
				return (NULL);
			tmp_pipe->left->pipe = (t_pipe *)malloc(sizeof(t_pipe));
			if (!tmp_pipe->left->pipe)
				return (NULL);
			tmp_pipe = tmp_pipe->left->pipe;
			(*pipes)--;
		}
		else
		{
			tmp_pipe->left = malloc(sizeof(t_left));
			if (!tmp_pipe->left)
				return (NULL);
			tmp_pipe->left->cmd = tmp[*i];
			tmp_pipe->left_type = PIPE_CMD;
			(*i)++;
		}
	}
	return (tmp_pipe);
}

t_pipe	*assign_cmd_to_pipe(t_pipe *tmp_pipe, t_cmd **tmp, int *i, int *pipes)
{
	tmp_pipe = assign_cmd_to_right(tmp_pipe, tmp, i);
	tmp_pipe = assign_cmd_to_left(tmp_pipe, tmp, i, pipes);
	return (tmp_pipe);
}

t_pipe	*build_tree(t_cmd **cmd)
{
	int		i;
	int		pipes;
	int 	cmd_count;
	t_pipe	*root;
	t_cmd	**tmp;
	t_pipe	*tmp_pipe;

	i = 0;
	pipes = pipes_in_cmds(cmd);
	cmd_count = pipes + 1;
	tmp = cmd;
	root = (t_pipe *)malloc(sizeof(t_pipe));
	if (!root)
		return (NULL);
	root->left = NULL;
	root->right = NULL;
	tmp_pipe = root;
	while (i < cmd_count)
	{
		tmp_pipe = assign_cmd_to_pipe(tmp_pipe, tmp, &i, &pipes);
		if (!tmp_pipe)
			return (NULL);
	}
	print_tree(root);
	return (root);
}

int	pipes_in_cmds(t_cmd **cmd)
{
	int	count;

	count = 0;
	while (cmd[count])
		count++;
	return (count - 1);
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
