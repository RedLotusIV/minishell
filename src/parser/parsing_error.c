/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:37:35 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/22 22:18:21 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	checking_parsing(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!current->next)
				return (parsing_error("|", 2));
			else if (current == head)
				return (parsing_error("|", 2));
		}
		else if (current->type == REDIR || current->type == HEREDOC
			|| current->type == INPUT || current->type == APPEND)
		{
			if (!current->next)
				return (parsing_error("newline", 2));
			else if (current->next->type != WORD)
				(parsing_error(current->next->value, 2));
		}
		current = current->next;
	}
}

void	parsing_error(char *message, int status)
{
	(void)status;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("'\n", 2);
}
