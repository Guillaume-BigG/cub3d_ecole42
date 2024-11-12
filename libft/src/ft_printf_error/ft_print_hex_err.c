/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:12:48 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 16:07:07 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

int	ft_hex_len_err(unsigned int i)
{
	int	len;

	len = 0;
	if (i == 0)
		return (1);
	while (i != 0)
	{
		i /= 16;
		len++;
	}
	return (len);
}

int	ft_count_width_hex_err(t_print_er *format, int k, unsigned int i)
{
	int	len;
	int	size;

	size = ft_hex_len_err(i);
	len = 0;
	if (format->plus && format->space)
		len++;
	else if (format->plus || format->space)
		len++;
	else if (format->hastag)
		len += 2;
	else if (i == 0 && format->precision_flag && format->precision == 0)
		return (format->width + 1 - k - size - len);
	if (format->width <= k + size + len)
		return (0);
	else
		return (format->width - k - size - len);
}

int	ft_count_prec_hex_err(t_print_er *format, int i)
{
	if (i == 0)
		return (format->precision);
	if (format->precision > i)
		return (format->precision - i);
	else
		return (0);
}

void	ft_hex_convert_err(t_print_er *format, unsigned int i, int flag)
{
	char	*low;
	char	*up;

	low = "0123456789abcdef";
	up = "0123456789ABCDEF";
	if (flag == 1)
	{
		if (i >= 16)
			ft_hex_convert_err(format, i / 16, flag);
		format->count += write(2, &low[i % 16], 1);
	}
	else
	{
		if (i >= 16)
			ft_hex_convert_err(format, i / 16, flag);
		format->count += write(2, &up[i % 16], 1);
	}
}

void	ft_print_hex_err(t_print_er *format, int flag)
{
	unsigned int	i;
	int				k;
	int				m;

	i = va_arg(format->args, unsigned int);
	k = ft_count_prec_hex_err(format, ft_hex_len_err(i));
	m = ft_count_width_hex_err(format, k, i);
	if (format->dash)
	{
		ft_flag_sign_err(format);
		ft_put_hashtag_err(format, flag, i);
		ft_zero_err(format, k);
		ft_cond_print_hex_err(format, i, flag);
		ft_space_err(format, m);
	}
	else
	{
		ft_check_zero_hex_err(format, flag, m, i);
		ft_cond_print_hex_err(format, i, flag);
	}
}
