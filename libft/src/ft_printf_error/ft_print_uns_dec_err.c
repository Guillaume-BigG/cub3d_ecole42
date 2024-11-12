/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uns_dec_err.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:45:12 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 16:04:55 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

int	ft_get_u_len_err(unsigned int i)
{
	unsigned int	len;

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

void	ft_putnbr_u_err(t_print_er *format, unsigned int n)
{
	unsigned int	i;

	i = n;
	if (i < 10)
		ft_putchar_err(format, i + 48);
	else
	{
		ft_putnbr_err(format, i / 10);
		ft_putnbr_err(format, i % 10);
	}
}

int	ft_count_prec_u_err(t_print_er *format, unsigned int i)
{
	if (i == 0)
		return (format->precision);
	if ((unsigned int)format->precision > i)
		return (format->precision - i);
	else
		return (0);
}

int	ft_count_width_u_err(t_print_er *format, int k, unsigned int i)
{
	int	len;
	int	size;

	len = 0;
	size = ft_get_u_len_err(i);
	if (format->plus && format->space)
		len++;
	else if (format->plus || format->space)
		len++;
	if (i == 0 && format->precision_flag && format->precision == 0)
		return (format->width + 1 - k - size - len);
	else
		return (format->width - k - size - len);
}

void	ft_print_uns_dec_err(t_print_er *format)
{
	unsigned int	i;
	int				sign;
	int				k;
	int				m;

	i = va_arg(format->args, unsigned int);
	sign = ft_check_sign_err(i);
	k = ft_count_prec_u_err(format, ft_get_u_len_err(i));
	m = ft_count_width_u_err(format, k, i);
	if (format->dash)
	{
		ft_flag_sign_err(format);
		ft_zero_err(format, k);
		ft_cond_print_unsint_err(format, i);
		ft_space_err(format, m);
	}
	else
	{
		ft_check_zero_err(format, m, sign);
		ft_zero_err(format, k);
		ft_cond_print_unsint_err(format, i);
	}
}
