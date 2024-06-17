/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:45:41 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/17 18:50:35 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	**mini_parsing(char *command)
{
	char	**result;
	int		i;
	int		j;
	int		k;
	int		count;
	int		l;
	char	tmp;

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
		while (command[i] == ' ' || command[i] == '\t' || command[i] == '\n'
			|| command[i] == '\v' || command[i] == '\f' || command[i] == '\r')
			i++;
		j = i;
		if (command[i] == '\"' || command[i] == '\'')
		{
			while(command[i])
			{
				if (command[i] == '\"' || command[i] == '\'')
				{
					tmp = command[i];
					i++;
					while (command[i] && command[i] != tmp)
						i++;
					if (command[i] == tmp)
						i++;
				}
				else
					break;
			}
		}
		if (command[i] && (command[i] == '|' || command[i] == '<'
				|| command[i] == '>') && (j == i))
		{
			if (command[i + 1] == command[i] && command[i] != '|')
				i += 2;
			else
				i++;
		}
		else if (command[i] && (command[i] != '|' && command[i] != '<'
				&& command[i] != '>'))
		{
			while (command[i] && command[i] != '|' && command[i] != '<'
				&& command[i] != '>' && command[i] != ' ' && command[i] != '\t'
				&& command[i] != '\n')
				i++;
		}
		if (i != j)
		{
			l = 0;
			result[k] = malloc(i - j + 1);
			if (!result[k])
				return (NULL);
			while (j < i)
			{
				if (command[j] == '\"')
				{
					j++;
					while (command[j] && command[j] != '\"')
					{
						result[k][l] = command[j];
						j++;
						l++;
					}
					if (command[j] == '\"')
						j++;
					else
						break ;
				}
				else if (command[j] == '\'')
				{
					j++;
					while (command[j] && command[j] != '\'')
					{
						result[k][l] = command[j];
						j++;
						l++;
					}
					if (command[j] == '\'')
						j++;
					else
						break ;
				}
				else if (command[j])
				{
					result[k][l] = command[j];
					l++;
					j++;
				}
			}
			result[k][l] = '\0';
			k++;
			printf("len = %d\n", l);
		}
	}
	result[k] = NULL;
	return (result);
}

int count_parse(char *command)
{ 
		int i;
		int l;
		char tmp;

	if (!command)
		return (0);
	i = 0;
	l = 0;
	while (command[i])
	{
		while (command[i] == ' ' || command[i] == '\t' || command[i] == '\n'
			|| command[i] == '\v' || command[i] == '\f' || command[i] == '\r')
			i++;
		if (command[i] && (command[i] == '|' || command[i] == '<'
				|| command[i] == '>'))
		{
			l++;
			if (command[i + 1] == command[i] && command[i] != '|')
				i += 2;
			else
				i++;
		}
		else if (command[i] && (command[i] == '\"' || command[i] == '\''))
		{
			if ((command[i - 1] != '\'' && command[i - 1] != '\"') || !i)
				l++;
			tmp = command[i];
			i++;
			while (command[i] && command[i] != tmp)
				i++;
			if (command[i] == tmp)
				i++;
		}
		else if (command[i] && (command[i] != '|' && command[i] != '<'
				&& command[i] != '>'))
		{
			if (command[i - 1] != tmp || !i)
				l++;
			while (command[i] && command[i] != '|' && command[i] != '<'
				&& command[i] != '>' && command[i] != ' ' && command[i] != '\t'
				&& command[i] != '\n')
				i++;
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
