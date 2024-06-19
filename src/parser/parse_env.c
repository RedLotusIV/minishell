/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:39:25 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/19 17:21:10 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char **set_path(char **env)
{
	char **envp;
	int i;
	
	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	envp = ft_split(env[i] + 5, ':');
	return (envp);
}