/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:27:10 by kevwang           #+#    #+#             */
/*   Updated: 2025/05/02 12:27:12 by kevwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_afficher(const char *str, int i, va_list args)
{
	int	count;

	count = 0;
	if (str[i + 1] == 'c')
		count += ft_putchar(va_arg(args, int));
	if (str[i + 1] == 's')
		count += ft_putstr(va_arg(args, char *));
	if (str[i + 1] == 'd')
		count += ft_putnbr(va_arg(args, int));
	if (str[i + 1] == 'i')
		count += ft_putnbr(va_arg(args, int));
	if (str[i + 1] == 'x')
		count += ft_puthexa_lower(va_arg(args, unsigned int));
	if (str[i + 1] == 'X')
		count += ft_puthexa_upper(va_arg(args, unsigned int));
	if (str[i + 1] == 'u')
		count += ft_putunsigned(va_arg(args, unsigned int));
	if (str[i + 1] == 'p')
		count += ft_putpointer(va_arg(args, void *));
	if (str[i + 1] == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		count;

	if (!str)
		return (-1);
	count = 0;
	va_start(args, str);
	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			count += ft_putchar(str[i]);
			i++;
		}
		else if (str[i] == '%')
		{
			count = count + ft_afficher(str, i, args);
			i = i + 2;
		}
	}
	va_end(args);
	return (count);
}
