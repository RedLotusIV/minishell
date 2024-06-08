/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:29:40 by amouhand          #+#    #+#             */
/*   Updated: 2024/05/30 19:53:08 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	allocate_cmd(t_cmd *cmd, t_token *token)
{
	// i should count how many commands i have in the tokens, meaning the number of pipes + 1
	// i should allocate the number of commands i have
	// i should then link the commands together as a doubly linked list
	// i should then allocate the number of arguments i have in each command as a char **
	// so in the end i should have a doubly linked list of commands, each command has a char ** of arguments and a t_token of redirections
	// which will make it so easy to be executed in the execution part, with pipes and redirections and everything
}
t_cmd	*parse_cmd(t_token *head)
{
	int i;
	t_cmd	*cmd;
	t_token	*tmp;

	i = 0;
	tmp = head;
	while (tmp)
	{
		cmd = malloc(sizeof(t_cmd));

	}
}