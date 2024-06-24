/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:39:25 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/23 15:15:53 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	**set_path(char **env)
{
	char	**envp;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5))
		i++;
	envp = ft_split(env[i] + 5, ':');
	return (envp);
}

char	*set_cwd(void)
{
	char *cwd;
	char *prompt;
	char *tmp;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_putstr_fd("Error: Can't Get Current Working Directory\n", 2);
	prompt = ft_strjoin( "minishell$", cwd);
	free(cwd);
	if (!prompt)
		ft_putstr_fd("Error: Can't Allocate Memory\n", 2);
	tmp = prompt;
	prompt = ft_strjoin(prompt, ": ");
	free(tmp);
	if (!prompt)
		ft_putstr_fd("Error: Can't Allocate Memory\n", 2);
	return (prompt);
}