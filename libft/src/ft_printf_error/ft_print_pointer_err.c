/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_err.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:53:34 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 11:55:38 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

int	ft_len_pointer_err(unsigned long p)
{
	int	len;

	len = 0;
	while (p > 0)
	{
		p /= 16;
		len++;
	}
	return (len);
}

int	ft_count_width_pointer_err(t_print_er *format, unsigned long p)
{
	int	len;
	int	size;

	size = ft_len_pointer_err(p);
	if (p == 0)
		len = 5;
	else if (size == 6)
		len = 8;
	else
		len = size + 2;
	if (format->plus && format->space)
		len++;
	else if (format->plus || format->space)
		len++;
	if (format->width <= len)
		return (0);
	else
	{
		return (format->width - len);
	}
}

void	ft_pointer_convert_err(t_print_er *format, unsigned long p)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (p >= 16)
		ft_pointer_convert_err(format, p / 16);
	format->count += write(2, &hex[p % 16], 1);
}

void	ft_check_pointer_err(t_print_er *format, unsigned long p)
{
	if (p == 0)
		format->count += write(2, "(nil)", 5);
	else
	{
		format->count += write(2, "0x", 2);
		ft_pointer_convert_err(format, p);
	}
}

void	ft_print_pointer_err(t_print_er *format)
{
	unsigned long	p;
	int				m;

	p = va_arg(format->args, unsigned long);
	m = ft_count_width_pointer_err(format, p);
	if (format->dash)
	{
		ft_flag_sign_err(format);
		ft_check_pointer_err(format, p);
		ft_space_err(format, m);
	}
	else
	{
		ft_space_err(format, m);
		ft_flag_sign_err(format);
		ft_check_pointer_err(format, p);
	}
}
