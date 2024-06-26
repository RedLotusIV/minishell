/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:54:04 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/24 18:07:28 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	testing_commands(t_pipe *root, char **path)
{
	t_pipe	*tmp;
	char	*tmp_path;

	tmp = root;
	while (tmp)
	{
		if (tmp->right)
		{
			if (tmp->right->args)
			{
				tmp_path = get_path(tmp->right->args[0], path);
				if (!tmp_path)
					printf("minishell: %s: command not found\n",
						tmp->right->args[0]);
				free(tmp_path);
			}
		}
		if (tmp->left)
		{
			if (tmp->left_type == PIPE_CMD)
			{
				tmp_path = get_path(tmp->left->cmd->args[0], path);
				if (!tmp_path)
					printf("minishell: %s: command not found\n",
						tmp->left->cmd->args[0]);
				free(tmp_path);
			}
			else
				tmp = tmp->left->pipe;
		}
		tmp = NULL;
	}
}

char	*get_path(char *command, char **path)
{
	int		i;
	char	*tmp;
	char	*to_free;

	if (!command || !path)
		return (NULL);
	i = 0;
	if (!ft_strcmp(command, "cd") || !ft_strcmp(command, "export")
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "exit")
		|| !ft_strcmp(command, "echo") || !ft_strcmp(command, "pwd")
		|| !ft_strcmp(command, "env"))
		return (ft_strdup(command));
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		to_free = tmp;
		tmp = ft_strjoin(tmp, command);
		free(to_free);
		if (!access(tmp, F_OK))
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}
