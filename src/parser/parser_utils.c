/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:45:41 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/08 03:32:28 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

// char	**mini_parsing(char **commands)
// {
// 	char	**result;
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		count;

// 	// char **original;
// 	// original = duplicate_pointer_array(commands);
// 	count = count_parse(commands);
// 	i = 0;
// 	k = 0;
// 	result = malloc(sizeof(char *) * (count + 1));
// 	if (!result)
// 		return (NULL);
// 	while (commands[i])
// 	{
// 		j = 0;
// 		while (commands[i][j])
// 		{
// 			if (commands[i][j] == '|' || commands[i][j] == '>'
// 				|| commands[i][j] == '<')
// 			{
// 				if (j != 0)
// 				{
// 					result[k] = ft_substr(commands[i], 0, j);
// 					k++;
// 				}
// 				if (commands[i][j + 1] == commands[i][j])
// 				{
// 					result[k] = ft_substr(commands[i], j, 2);
// 					j += 2;
// 				}
// 				else
// 				{
// 					result[k] = ft_substr(commands[i], j, 1);
// 					j += 1;
// 				}
// 				k++;
// 				commands[i] = commands[i] + j;
// 				j = 0;
// 			}
// 			else
// 				j++;
// 		}
// 		if (commands[i][0] != '\0')
// 		{
// 			result[k] = ft_strdup(commands[i]);
// 			if (!result[k])
// 				return (NULL);
// 			k++;
// 		}
// 		i++;
// 	}
// 	result[k] = NULL;
// 	// free_strings(original);
// 	return (result);
// }
char	**mini_parsing(char *command)
{
	char	**result;
	int		i;
	int		j;
	int		k;
	int		count;

	if (!command)
		return (NULL);
	count = count_parse(command);
	if (!count)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	printf("count = %d\n", count);
	while (command[i])
	{
		while(command[i] == ' ' || command[i] == '\t' || command[i] == '\n'
			|| command[i] == '\v' || command[i] == '\f' || command[i] == '\r')
			i++;
		j = i;
		if (command[i] == '\"')
		{
			i++;
			while (command[i] && command[i] != '\"')
				i++;
			if (command[i] == '\"')
				i++;
		}
		else
		{
			if (command[i] && (command[i] == '|' || command[i] == '<' || command[i] == '>'))
			{
				if (command[i + 1] == command[i])
					i += 2;
				else
					i++;
			}
			else if (command[i] && (command[i] != '|' && command[i] != '<' && command[i] != '>'))
			{
				while (command[i] && command[i] != '|' && command[i] != '<' && command[i] != '>'
				&& command[i] != ' ' && command[i] != '\t' && command[i] != '\n')
					i++;
		}
		}
		if (i != j)
		{
			result[k] = ft_substr(command, j, i - j);
			if (!result[k])
				return (NULL);
			// re allocating, so i should free the original string
			result[k] = ft_strtrim(result[k], "\"");
			k++;
		}
	}
	result[k] = NULL;
	return (result);
}

int	count_parse(char *command)
{
	int	i;
	int	l;

	if (!command)
		return (0);
	i = 0;
	l = 0;
	//"    <<infile ls -al|cat|wc -l>>outfile    "
	while (command[i])
	{
		while(command[i] == ' ' || command[i] == '\t' || command[i] == '\n'
			|| command[i] == '\v' || command[i] == '\f' || command[i] == '\r')
			i++;
		if (command[i] == '\"')
		{
			i++;
			while (command[i] && command[i] != '\"')
				i++;
			if (command[i] == '\"')
				i++;
			l++;
		}
		else
		if (command[i] && (command[i] == '|' || command[i] == '<' || command[i] == '>'))
		{
			l++;
			if (command[i + 1] == command[i])
				i += 2;
			else
				i++;
		}
		else if (command[i] && (command[i] != '|' && command[i] != '<' && command[i] != '>'))
		{
			while (command[i] && command[i] != '|' && command[i] != '<' && command[i] != '>'
			 && command[i] != ' ' && command[i] != '\t' && command[i] != '\n')
				i++;
			l++;
		}
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