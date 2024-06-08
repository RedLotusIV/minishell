/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexa_pf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:37:43 by amouhand          #+#    #+#             */
/*   Updated: 2024/03/18 05:37:33 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhexa_pf(unsigned int n, int x, int *len, int *flag)
{
	char	*form;
	int		remainder;

	remainder = 0;
	if (x == 'x')
		form = "0123456789abcdef";
	else
		form = "0123456789ABCDEF";
	if (n != 0)
	{
		*flag = 1;
		(*len)++;
		remainder = n % 16;
		ft_printhexa_pf(n / 16, x, len, flag);
		ft_putchar_pf(form[remainder]);
	}
	if (*flag == 0 && !n)
		return (ft_putchar_pf('0'));
	return (*len);
}
