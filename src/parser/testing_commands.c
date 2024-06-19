/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:54:04 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/19 17:44:54 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	testing_commands(t_pipe *root, char **path)
{
	t_pipe	*tmp;

	tmp = root;
	while (tmp)
	{
		if (tmp->right)
		{
			if (!get_path(tmp->right->args[0], path))
				printf("minishell: %s: command not found\n", tmp->right->args[0]);
		}
		if (tmp->left)
		{
			if (tmp->left_type == PIPE_CMD)
			{
				if (!get_path(tmp->left->cmd->args[0], path))
					printf("minishell: %s: command not found\n", tmp->left->cmd->args[0]);
			}
			else
				tmp = tmp->left->pipe;
		}
		tmp = NULL;
	}
}

char *get_path(char *command, char **path)
{
	int i;
	char *tmp;

	if (!command || !path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, command);
		if (!access(tmp, F_OK))
			return (tmp);
		i++;
	}
	return (NULL);
}