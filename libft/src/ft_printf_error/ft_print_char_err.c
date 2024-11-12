/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_err.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 18:26:50 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 11:53:41 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printferr.h"

// ft_count_width is in the string file

void	ft_print_char_err(t_print_er *format)
{
	unsigned char	c;
	int				k;

	k = ft_count_width_err(format, 1);
	c = va_arg(format->args, int);
	if (format->dash)
	{
		ft_putchar_err(format, c);
		ft_space_err(format, k);
	}
	else
	{
		ft_space_err(format, k);
		ft_putchar_err(format, c);
	}
}
