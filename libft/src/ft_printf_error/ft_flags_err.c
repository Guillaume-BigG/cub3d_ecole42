/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:21:57 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 11:53:25 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

int	ft_len_digit_err(t_print_er *format, const char *str, int i)
{
	if (str[i - 1] == '.')
	{
		while (ft_isdigit(str[i]))
		{
			format->precision = format->precision * 10 + (str[i] - 48);
			format->precision_flag = 1;
			i++;
		}
	}
	else
	{
		while (ft_isdigit(str[i]))
		{
			format->width = format->width * 10 + (str[i] - 48);
			format->width_flag = 1;
			i++;
		}
	}
	return (i);
}

void	ft_convert_err(t_print_er *format, const char *str, int i)
{
	if (str[i] == 'c')
		ft_print_char_err(format);
	else if (str[i] == 's')
		ft_print_str_err(format);
	else if (str[i] == 'p')
		ft_print_pointer_err(format);
	else if (str[i] == 'i' || str[i] == 'd')
		ft_print_intdec_err(format);
	else if (str[i] == 'u')
		ft_print_uns_dec_err(format);
	else if (str[i] == 'x')
		ft_print_hex_err(format, 1);
	else if (str[i] == 'X')
		ft_print_hex_err(format, 0);
	else if (str[i] == '%')
		ft_putchar_err(format, '%');
	else
		return ;
}

int	ft_check_flag_err(t_print_er *format, const char *str, int i)
{
	if (str[i] == '0' || str[i] == '-' || str[i] == '#' || str[i] == ' '
		|| str[i] == '+' || str[i] == '.')
	{
		if (str[i] == '0')
			format->zero = 1;
		if (str[i] == '-')
			format->dash = 1;
		if (str[i] == '#')
			format->hastag = 1;
		if (str[i] == ' ')
			format->space = 1;
		if (str[i] == '+')
			format->plus = 1;
		if (str[i] == '.')
			format->precision_flag = 1;
		i++;
	}
	else if (ft_isdigit(str[i]))
		i = ft_len_digit_err(format, str, i);
	return (i);
}

int	ft_flags_err(t_print_er *format, const char *str, int i)
{
	while (str[i] != 'c' && str[i] != 's' && str[i] != 'p' && str[i] != 'd'
		&& str[i] != 'i' && str[i] != 'u' && str[i] != 'x' && str[i] != 'X'
		&& str[i] != '%')
	{
		i = ft_check_flag_err(format, str, i);
	}
	if (format->precision_flag == 0 && format->width_flag == 0)
		format->no_flags = 1;
	ft_convert_err(format, str, i);
	return (i);
}
