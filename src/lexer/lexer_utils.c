/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 01:38:09 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/18 18:02:31 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_strcpy(char *dst, char *src)
{
	int	i;

	if (!src)
		return ;
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

// void	free_parser(t_parser *s)
// {
// 	t_token *current;
// 	t_token *tmp;

// 	tmp = s->head;
// 	while (tmp)
// 	{
// 		current = tmp;
// 		free(current->value);
// 		free(current);
// 		tmp = tmp->next;
// 	}
// 	if (s->line)
// 		free(s->line);
// 	if (s->result)
// 		free_strings(s->result);
// }