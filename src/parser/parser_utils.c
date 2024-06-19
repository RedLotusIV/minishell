/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:45:41 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/18 17:58:51 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	**mini_parsing(char *command)
{
	char	**result;
	int		i;
	int		j;
	int		k;

	if (setting_parser(command, &result, &i, &k))
		return (NULL);
	while (command[i])
	{
		i = skip_whitespace(command, i);
		j = i;
		if (command[i] == '\"' || command[i] == '\'')
			i = skip_quotes(command, i);
		if (command[i] && (command[i] == '|' || command[i] == '<'
				|| command[i] == '>') && (j == i))
			i = skip_special_char(command, i);
		else
			i = skip_everything_else(command, i);
		if (i != j)
			result[++k] = copy_segment(command, j, i);
	}
	result[++k] = NULL;
	return (result);
}

int	count_parse(char *command)
{
	int	i;
	int	l;
	int	tmp;

	i = 0;
	l = 0;
	tmp = 0;
	if (!command)
		return (0);
	while (command[i])
	{
		i = skip_whitespace(command, i);
		if (command[i] && (command[i] == '|' || command[i] == '<'
				|| command[i] == '>'))
			i = handle_special_characters(command, i, &l);
		else if (command[i] && (command[i] == '\"' || command[i] == '\''))
			i = handle_quotes(command, i, &l, &tmp);
		else if (command[i])
			i = handle_regular_characters(command, i, &l, &tmp);
	}
	printf("length = %d\n", l);
	return (l);
}

int	setting_parser(char *command, char ***result, int *i, int *k)
{
	int	count;

	*i = 0;
	*k = -1;
	if (!command)
		return (1);
	count = count_parse(command);
	if (!count)
		return (1);
	*result = malloc(sizeof(char *) * (count + 1));
	if (!(*result))
		return (1);
	return (0);
}
