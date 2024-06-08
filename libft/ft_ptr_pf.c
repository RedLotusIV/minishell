/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_pf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouhand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:41:43 by amouhand          #+#    #+#             */
/*   Updated: 2024/03/18 06:20:19 by amouhand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ptr_pf(unsigned long ptr, int *flag, int *len, int *nill_check)
{
	char	*form;
	int		remainder;

	remainder = 0;
	form = "0123456789abcdef";
	if (!ptr && *nill_check == 0)
		return (ft_putstr_pf("(nil)"));
	if (*flag == 0)
	{
		ft_putstr_pf("0x");
		*flag = 1;
	}
	if (ptr)
	{
		(*len)++;
		*nill_check = 1;
		remainder = ptr % 16;
		ft_ptr_pf(ptr / 16, flag, len, nill_check);
		ft_putchar_pf(form[remainder]);
	}
	return (*len + 2);
}
