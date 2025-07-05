/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putsunsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:48:18 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/05 14:48:42 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putunsigned_print(unsigned int n)
{
	if (n > 9)
	{
		ft_putunsigned_print(n / 10);
	}
	write(1, &"0123456789"[n % 10], 1);
}

int	ft_putunsigned(unsigned int n)
{
	int	count;

	count = 1;
	ft_putunsigned_print(n);
	while (n > 9)
	{
		count++;
		n = n / 10;
	}
	return (count);
}
