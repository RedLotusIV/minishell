/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:39:25 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/19 21:31:51 by amouhand         ###   ########.fr       */
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
char *set_pwd(char *prompt)
{
	replaceWord(prompt, ft_strjoin("/home/", getenv("USER")), "~");
	return (prompt);
}

void replaceWord(char* str, char* oldword, char* newword)
{
	char *pos;
	char temp[1000];
	int index;
	int owlen;

	index = 0;
	owlen = ft_strlen(oldword);
	pos = strstr(str, oldword);
	while (pos)
	{
		ft_strcpy(temp, str);
		index = pos - str;
		str[index] = '\0';
		strcat(str, newword);
		strcat(str, temp + index + owlen);
		pos = strstr(str, oldword);
	}
}