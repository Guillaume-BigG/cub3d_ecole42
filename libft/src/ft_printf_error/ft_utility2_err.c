/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility2_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 18:17:08 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 16:03:59 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

// return a char for the INT/DEC based on the zero and preci flag
char	ft_flag_prec_int_err(t_print_er *format)
{
	if (format->precision_flag && format->zero)
		return ('A');
	else if (format->precision_flag && !(format->zero))
		return ('A');
	else if (!(format->precision_flag) && format->zero)
		return ('B');
	else
		return ('C');
}

// tell if a parameter sent is neg or positif
int	ft_check_sign_err(int i)
{
	if (i < 0)
		return (0);
	else
		return (1);
}

// return a char telling if as to print a zero or a space for the unsigned int
void	ft_check_zero_err(t_print_er *format, int m, int sign)
{
	if (ft_flag_prec_int_err(format) == 'A'
		|| ft_flag_prec_int_err(format) == 'C')
	{
		ft_space_err(format, m);
		if (sign)
			ft_flag_sign_err(format);
	}
	else
	{
		if (sign)
			ft_flag_sign_err(format);
		ft_zero_err(format, m);
	}
}

// print a hashtag for the xX based on flag and special case
void	ft_put_hashtag_err(t_print_er *format, int flag, unsigned int i)
{
	if (format->hastag && i != 0)
	{
		if (flag == 1)
			format->count += write(2, "0x", 2);
		else
			format->count += write(2, "0X", 2);
	}
}
