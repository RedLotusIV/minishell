/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 20:18:48 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/20 20:26:00 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/executor.h"

int	execute_commands(t_pipe *root)
{
	t_pipe	*tmp;

	tmp = root;
	while (tmp)
	{
		if (tmp->right)
		{
			if (!ft_strcmp(tmp->right->args[0], "cd"))
				cd(tmp->right);
		}
		if (tmp->left)
		{
			if (tmp->left_type == PIPE_CMD)
			{
				if (!ft_strcmp(tmp->left->cmd->args[0], "cd"))
					cd(tmp->left->cmd);
			}
			else
				tmp = tmp->left->pipe;
		}
		tmp = NULL;
	}
	return (0);	
}