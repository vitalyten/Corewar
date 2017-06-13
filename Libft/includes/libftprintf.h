/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 08:24:21 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/14 15:53:05 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "./libft.h"
# include <limits.h>
# include <stdio.h>

# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

typedef struct	s_flags
{
	int			space;
	int			neg;
	int			pos;
	int			hashtag;
	int			zero;
}				t_flags;

typedef struct	s_env
{
	int			i;
	int			size;
	int			flag;
	int			type;
	int			conv;
	int			precision;
	int			width;
	int			zero_width;
	char		modif;
	int			dual;
	int			color;
	int			parsed;
	t_flags		flags;
}				t_env;

int				ft_strlen(char *str);
int				ft_putchar(char c);
int				ft_putstr(const char *s);
void			ft_putoctal(unsigned long long nb);
int				ft_size_nbr(long long n);
void			ft_putnbr(long long n);
void			ft_puthexa(unsigned long long nb, const char *base);
void			ft_putunsigned(unsigned long long n);
void			ft_memdel(void **ap);
void			ft_putabs(long long n);
int				ft_printf(const char *format, ...);
int				check_type(char c, t_env *env);
void			print_arg(va_list ap, t_env *env, char type);
int				get_width(const char *format, int i, t_env *env);
int				get_space_di(t_env *env, long long nb, int zero);
int				get_precision(const char *format, int i, t_env *env);
int				get_precision_star(t_env *env, va_list ap);
void			ft_print_un(int space, int zero, t_env *env);
int				ft_size_abs(long long n);
int				ft_size_hexoc(unsigned long long nb, int base);
int				ft_size_unsigned(unsigned long long n);
int				ft_size_bin(unsigned int nb);
void			ft_putunsigned_cap(unsigned long long n);
int				ft_print_c(va_list ap, t_env *env);
int				ft_print_s(va_list ap, t_env *env);
int				ft_print_o(va_list ap, t_env *env);
int				ft_print_o_cap(va_list ap, t_env *env);
int				ft_print_x(va_list ap, t_env *env);
int				ft_print_di(va_list ap, t_env *env);
int				ft_print_d_cap(va_list ap, t_env *env);
int				ft_print_p(va_list ap, t_env *env);
int				ft_print_xcap(va_list ap, t_env *env);
int				ft_print_pe(va_list ap, t_env *env);
int				ft_print_u(va_list ap, t_env *env);
int				ft_print_u_cap(va_list ap, t_env *env);
int				ft_print_s_cap(va_list ap, t_env *env);
int				ft_print_c_cap(va_list ap, t_env *env);
int				print_precision_di(long long nb, t_env *env);
int				print_precision_s(char *str, t_env *env);
int				print_precision_x(unsigned long long nb,
					t_env *env, const char *base);
int				print_precision_o(unsigned int nb, t_env *env);
int				print_width_str(char *str, t_env *env);
int				print_width_neg_o(unsigned long long nb, t_env *env);
int				print_width_u(unsigned long long nb, t_env *env);
int				print_preciwidth_di(long long nb, t_env *env);
int				print_precision_u(unsigned long long nb, t_env *env);
void			add_flag(t_env *env, char value);
int				check_flag(char c);
int				handle_flags_x(t_env *env, unsigned long long nb,
				const char *base, int cap);
int				handle_flags_o(t_env *env, unsigned long long nb);
int				handle_flags_u(t_env *env, unsigned long long nb);
int				ft_check_modif(char c);
int				get_modif(const char *format, int i, t_env *env);
intmax_t		convert(va_list ap, t_env *env);
uintmax_t		convert_u(va_list ap, t_env *env);
void			clean_env(t_env *env);

#endif
