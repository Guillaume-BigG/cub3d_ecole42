/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printferr.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbeaudoi <gbeaudoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:29:44 by gbeaudoi          #+#    #+#             */
/*   Updated: 2024/10/31 16:06:08 by gbeaudoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTFERR_H
# define FT_PRINTFERR_H

# include "../include/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_print_er
{
	va_list	args;
	int		width;
	int		precision;
	int		zero;
	int		dot;
	int		dash;
	int		hastag;
	int		plus;
	int		count;
	int		width_flag;
	int		precision_flag;
	int		space;
	int		no_flags;
}			t_print_er;

int			ft_printf_err_err(const char *str, ...);
t_print_er	*ft_initialize_err(t_print_er *format);
void		ft_putchar_err(t_print_er *format, char c);
void		ft_zero_err(t_print_er *format, int i);
void		ft_space_err(t_print_er *format, int i);
void		ft_flag_sign_err(t_print_er *format);
char		ft_flag_dash_err(t_print_er *format);
char		ft_flag_prec_int_err(t_print_er *format);
int			ft_isdigit(int c);
int			ft_check_sign_err(int i);
void		ft_check_zero_err(t_print_er *format, int m, int sign);
int			ft_len_digit_err(t_print_er *format, const char *str, int i);
void		ft_convert_err(t_print_er *format, const char *str, int i);
int			ft_flags_err(t_print_er *format, const char *str, int i);
void		ft_print_char_err(t_print_er *format);
int			ft_count_width_err(t_print_er *format, int k);
int			ft_count_prec_err(t_print_er *format, char *str);
void		ft_print_str_err(t_print_er *format);
size_t		ft_strlen(const char *str);
int			ft_count_width_pointer_err_err(t_print_er *format, unsigned long p);
void		ft_pointer_convert_err_err(t_print_er *format, unsigned long p);
void		ft_print_pointer_err(t_print_er *format);
int			ft_get_di_len_err(int i);
void		ft_putnbr_err(t_print_er *format, int n);
int			ft_count_prec_id_err(t_print_er *format, int i);
int			ft_count_width_id_err(t_print_er *format, int k, int sign, int i);
void		ft_print_intdec_err(t_print_er *format);
int			ft_get_u_len_err(unsigned int i);
void		ft_putnbr_u_err(t_print_er *format, unsigned int n);
int			ft_count_prec_u_err(t_print_er *format, unsigned int i);
int			ft_count_width_u_err(t_print_er *format, int k, unsigned int i);
void		ft_print_uns_dec_err(t_print_er *format);
int			ft_hex_len_err(unsigned int i);
int			ft_count_width_hex_err(t_print_er *format, int k, unsigned int i);
int			ft_count_prec_hex_err(t_print_er *format, int i);
void		ft_hex_convert_err(t_print_er *format, unsigned int i, int flag);
void		ft_put_hashtag_err(t_print_er *format, int flag, unsigned int i);
void		ft_print_hex_err(t_print_er *format, int flag);
void		ft_check_str_err(t_print_er *format, char *str, int k);
void		ft_check_zero_hex_err(t_print_er *format, int flag, int m,
				unsigned int i);
void		ft_check_pointer_err(t_print_er *format, unsigned long p);
void		ft_check_intdec_err(t_print_er *format, int k, int m, int i);
int			ft_len_pointer_err(unsigned long p);
void		ft_cond_print_int_err(t_print_er *format, int i);
void		ft_cond_print_unsint_err(t_print_er *format, unsigned int i);
void		ft_cond_print_hex_err(t_print_er *format, unsigned int i, int flag);

#endif