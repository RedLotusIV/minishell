/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <amouhand@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:01:37 by amouhand          #+#    #+#             */
/*   Updated: 2024/06/18 11:53:42 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

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