/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:01:37 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/18 18:00:22 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	skip_whitespace(char *command, int i)
{
	while (command[i] == ' ' || command[i] == '\t' || command[i] == '\n'
		|| command[i] == '\v' || command[i] == '\f' || command[i] == '\r')
		i++;
	return (i);
}

int	handle_special_characters(char *command, int i, int *l)
{
	(*l)++;
	if (command[i + 1] == command[i] && command[i] != '|')
		i += 2;
	else
		i++;
	return (i);
}

int	handle_quotes(char *command, int i, int *l, int *tmp)
{
	if ((command[i - 1] != '\'' && command[i - 1] != '\"') || !i)
		(*l)++;
	*tmp = command[i];
	i++;
	while (command[i] && command[i] != *tmp)
		i++;
	if (command[i] == *tmp)
		i++;
	return (i);
}

int	handle_regular_characters(char *command, int i, int *l, int *tmp)
{
	if (command[i - 1] != *tmp || i == 0)
		(*l)++;
	while (command[i] && command[i] != '|' && command[i] != '<'
		&& command[i] != '>' && command[i] != ' ' && command[i] != '\t'
		&& command[i] != '\n')
		i++;
	return (i);
}
