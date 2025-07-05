/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:50:38 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/05 14:50:40 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putptr_print(uintptr_t n)
{
	if (n > 15)
	{
		ft_putptr_print(n / 16);
	}
	write(1, &"0123456789abcdef"[n % 16], 1);
}

static int	ft_putptr(uintptr_t n)
{
	int	count;

	count = 1;
	ft_putptr_print(n);
	while (n > 15)
	{
		count++;
		n = n / 16;
	}
	return (count);
}

int	ft_putpointer(void *s)
{
	if (!s)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	return (ft_putptr((uintptr_t)s) + 2);
}
