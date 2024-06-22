/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:47:21 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/22 20:49:03 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

int	cd(t_cmd *cmd)
{
	char	*path;

	if (cmd->count > 2)
		return (ft_putstr_fd("cd: Error: Too Many Args\n", 2), 1);
	if (cmd->count == 1)
	{
		path = getenv("HOME");
		if (!path)
			return (ft_putstr_fd("cd: Error: HOME not set\n", 2), 1);
	}
	else
		path = cmd->args[1];
	if (chdir(path) == -1)
	{
		return (ft_putstr_fd("cd: Error: No Such File or Directory\n", 2), 1);
	}
	// getcwd(path, 1024);
	// printf("%s\n", path);
	return (0);
}
