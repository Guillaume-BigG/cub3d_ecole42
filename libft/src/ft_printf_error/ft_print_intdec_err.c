/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_intdec_err.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:30:27 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 16:06:48 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

int	ft_get_di_len_err(int i)
{
	int	len;

	len = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		i /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr_err(t_print_er *format, int n)
{
	unsigned int	i;

	if (n < 0)
		i = n * -1;
	else
		i = n;
	if (i < 10)
		ft_putchar_err(format, i + 48);
	else
	{
		ft_putnbr_err(format, i / 10);
		ft_putnbr_err(format, i % 10);
	}
}

int	ft_count_prec_id_err(t_print_er *format, int i)
{
	if (i == 0)
		return (format->precision);
	else if (format->precision > i)
		return (format->precision - i);
	else
		return (0);
}

int	ft_count_width_id_err(t_print_er *format, int k, int sign, int i)
{
	int	len;
	int	size;

	size = ft_get_di_len_err(i);
	len = 0;
	if (!sign)
		len++;
	else if (format->plus || format->space)
		len++;
	if (i == 0 && format->precision_flag && format->precision == 0)
		return (format->width + 1 - k - size - len);
	else if (format->width <= (k + size + len))
		return (0);
	else
		return (format->width - k - size - len);
}

void	ft_print_intdec_err(t_print_er *format)
{
	int	i;
	int	k;
	int	m;
	int	sign;

	i = va_arg(format->args, int);
	sign = ft_check_sign_err(i);
	k = ft_count_prec_id_err(format, ft_get_di_len_err(i));
	m = ft_count_width_id_err(format, k, sign, i);
	if (format->dash)
	{
		if (sign)
			ft_flag_sign_err(format);
		else
			ft_putchar_err(format, '-');
		ft_zero_err(format, k);
		ft_cond_print_int_err(format, i);
		ft_space_err(format, m);
	}
	else
	{
		ft_check_intdec_err(format, k, m, i);
		ft_cond_print_int_err(format, i);
	}
}
