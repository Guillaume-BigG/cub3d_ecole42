/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:50:37 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 16:04:29 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

t_print_er	*ft_initialize_err(t_print_er *format)
{
	format->width = 0;
	format->precision = 0;
	format->zero = 0;
	format->dot = 0;
	format->dash = 0;
	format->hastag = 0;
	format->plus = 0;
	format->count = 0;
	format->width_flag = 0;
	format->precision_flag = 0;
	format->space = 0;
	format->no_flags = 0;
	return (format);
}

int	ft_printf_err_err(const char *str, ...)
{
	int			i;
	t_print_er	*format;
	int			len;

	format = (t_print_er *)malloc(sizeof(t_print_er));
	if (format == NULL)
		return (-1);
	ft_initialize_err(format);
	va_start(format->args, str);
	i = -1;
	len = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '%')
		{
			i = ft_flags_err(format, str, i + 1);
			len += format->count;
			ft_initialize_err(format);
		}
		else
			len += write(2, &str[i], 1);
	}
	va_end(format->args);
	free(format);
	return (len);
}
