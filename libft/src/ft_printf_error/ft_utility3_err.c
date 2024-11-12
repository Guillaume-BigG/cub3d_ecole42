/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility3_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:47:44 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 16:06:29 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

void	ft_check_intdec_err(t_print_er *format, int k, int m, int i)
{
	int	sign;

	sign = ft_check_sign_err(i);
	if (sign)
	{
		ft_flag_sign_err(format);
		if ((format->zero && !format->precision_flag))
			ft_zero_err(format, m);
		else
			ft_space_err(format, m);
	}
	if (!sign)
	{
		if ((format->zero && !format->precision_flag))
		{
			ft_putchar_err(format, '-');
			ft_zero_err(format, m);
		}
		else
		{
			ft_space_err(format, m);
			ft_putchar_err(format, '-');
		}
	}
	ft_zero_err(format, k);
}

void	ft_cond_print_int_err(t_print_er *format, int i)
{
	if (format->precision_flag)
	{
		if (format->precision == 0)
		{
			if (i == 0)
				return ;
		}
	}
	if (i == 0)
		ft_putchar_err(format, '0');
	else
		ft_putnbr_err(format, i);
}

void	ft_cond_print_unsint_err(t_print_er *format, unsigned int i)
{
	if (format->precision_flag)
	{
		if (format->precision == 0)
		{
			if (i == 0)
				return ;
		}
	}
	if (i == 0)
		ft_putchar_err(format, '0');
	else
		ft_putnbr_u_err(format, i);
}

void	ft_check_zero_hex_err(t_print_er *format, int flag, int m,
		unsigned int i)
{
	if (ft_flag_dash_err(format) == 'A')
	{
		ft_space_err(format, m);
		ft_flag_sign_err(format);
		ft_put_hashtag_err(format, flag, i);
		ft_zero_err(format, ft_count_prec_hex_err(format, ft_hex_len_err(i)));
	}
	else if (ft_flag_dash_err(format) == 'C')
	{
		ft_flag_sign_err(format);
		ft_put_hashtag_err(format, flag, i);
		if (i == 0)
			ft_zero_err(format, m);
		else
			ft_space_err(format, m);
		ft_zero_err(format, ft_count_prec_hex_err(format, ft_hex_len_err(i)));
	}
	else
	{
		ft_flag_sign_err(format);
		ft_put_hashtag_err(format, flag, i);
		ft_zero_err(format, m);
		ft_zero_err(format, ft_count_prec_hex_err(format, ft_hex_len_err(i)));
	}
}

void	ft_cond_print_hex_err(t_print_er *format, unsigned int i, int flag)
{
	if (format->precision_flag)
	{
		if (format->precision == 0)
		{
			if (i == 0)
				return ;
		}
	}
	if (i == 0)
		ft_putchar_err(format, '0');
	else
		ft_hex_convert_err(format, i, flag);
}
