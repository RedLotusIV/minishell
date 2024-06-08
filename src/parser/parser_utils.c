/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:45:41 by amouhand          #+#    #+#             */
/*   Updated: 2024/05/30 19:09:35 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	**mini_parsing(char **commands)
{
	char	**result;
	int		i;
	int		j;
	int		k;
	int		count;

	// char **original;
	// original = duplicate_pointer_array(commands);
	count = count_parse(commands);
	i = 0;
	k = 0;
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			if (commands[i][j] == '|' || commands[i][j] == '>'
				|| commands[i][j] == '<')
			{
				if (j != 0)
				{
					result[k] = ft_substr(commands[i], 0, j);
					k++;
				}
				if (commands[i][j + 1] == commands[i][j])
				{
					result[k] = ft_substr(commands[i], j, 2);
					j += 2;
				}
				else
				{
					result[k] = ft_substr(commands[i], j, 1);
					j += 1;
				}
				k++;
				commands[i] = commands[i] + j;
				j = 0;
			}
			else
				j++;
		}
		if (commands[i][0] != '\0')
		{
			result[k] = ft_strdup(commands[i]);
			if (!result[k])
				return (NULL);
			k++;
		}
		i++;
	}
	result[k] = NULL;
	// free_strings(original);
	return (result);
}

int	count_parse(char **words)
{
	int	i;
	int	j;
	int	l;
	int	flag;

	i = 0;
	l = 0;
	//cant give a good count on "<infile" "ls|cat" "-l>outfile" gives 7 instead of the expected 8 {<< infile ls | cat -l >> outfile}
	//"<infile" "ls|cat" "-l>outfile"
	while (words[i])
	{
		j = 0;
		flag = 0;
		while (words[i][j])
		{
			if (flag == 1)
			{
				flag = 0;
				l++;
			}
			if (words[i][j - 1] != '\\' && (words[i][j] == '|'
					|| words[i][j] == '>' || words[i][j] == '<'))
			{
				flag = 1;
				l++;
				if (words[i][j + 1] == '|' || words[i][j + 1] == '>'
					|| words[i][j + 1] == '<')
					j++;
			}
			j++;
		}
		if (flag == 0)
			l++;
		i++;
	}
	return (l);
}

void	free_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	if (strings)
		free(strings);
}

char	**duplicate_pointer_array(char **commands)
{
	int i = 0;
	while (commands[i])
		i++;
	char **dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	for (i = 0; commands[i]; i++)
	{
		dup[i] = commands[i];
	}
	dup[i] = NULL;
	return (dup);
}