/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:50:02 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/05 14:50:04 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthexa_print(unsigned int n, char format)
{
	if (n > 15)
	{
		ft_puthexa_print(n / 16, format);
	}
	if (format == 'x')
		write(1, &"0123456789abcdef"[n % 16], 1);
	else
		write(1, &"0123456789ABCDEF"[n % 16], 1);
}

int	ft_puthexa_upper(unsigned int n)
{
	int	count;

	count = 1;
	ft_puthexa_print(n, 'X');
	while (n > 15)
	{
		count++;
		n = n / 16;
	}
	return (count);
}

int	ft_puthexa_lower(unsigned int n)
{
	int	count;

	count = 1;
	ft_puthexa_print(n, 'x');
	while (n > 15)
	{
		count++;
		n = n / 16;
	}
	return (count);
}
