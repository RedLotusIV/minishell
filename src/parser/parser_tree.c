/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:54:21 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/16 12:33:32 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_pipe	*build_tree(t_cmd **cmd)
{
	t_pipe	*root;

	root = (t_pipe *)malloc(sizeof(t_pipe));
	if (!root)
		return (NULL);
	
	return (root);
}