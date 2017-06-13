/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_xcap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 12:33:04 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/19 13:33:44 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	print_width(unsigned long long nb, t_env *env)
{
	int	width;
	int	i;

	i = 0;
	width = env->width - ft_size_hexoc(nb, 16);
	if (env->flags.hashtag == 1)
		width -= 2;
	if (env->flags.hashtag == 1 && nb != 0)
		env->size += ft_putstr("0X");
	while (width > i)
	{
		if (env->zero_width == 0 && env->flags.zero == 0)
			env->size += ft_putchar(' ');
		if (env->zero_width == 1 || env->flags.zero == 1)
			env->size += ft_putchar('0');
		i++;
	}
	if (env->flags.hashtag == 1 && nb != 0)
		env->size += ft_putstr("0X");
	return (0);
}

static int	print_width_precision(int nb, t_env *env)
{
	int	space;
	int	zero;
	int	size;

	zero = 0;
	size = ft_size_abs(nb);
	if (env->precision > size)
		zero = env->precision - size;
	if (env->precision == 0 && nb == 0)
		space = env->width;
	else if (zero != 0 && nb >= 0)
		space = env->width - zero - ft_size_hexoc(nb, 16);
	else if (zero == 0 && nb >= 0)
		space = env->width - ft_size_hexoc(nb, 16);
	else
		space = 0;
	ft_print_un(space, zero, env);
	if (env->precision == 0 && nb == 0)
		return (0);
	env->size += ft_size_nbr(nb);
	if (nb != 0)
		ft_puthexa(nb, "0123456789ABCDEF");
	return (0);
}

static int	print_preciwidth_x(unsigned long long nb,
	t_env *env, const char *base)
{
	int	i;
	int	size;
	int j;

	i = 0;
	j = 0;
	size = ft_size_hexoc(nb, 16);
	if (env->width > env->precision)
		print_width_precision(nb, env);
	else
	{
		if (size < env->precision)
		{
			i = env->precision - size;
			while (j < i)
			{
				env->size += ft_putchar('0');
				j++;
			}
		}
		if (nb != 0)
			ft_puthexa(nb, base);
		env->size += ft_size_hexoc(nb, 16);
	}
	return (size);
}

int			ft_print_xcap(va_list ap, t_env *env)
{
	unsigned long long	nb;

	nb = convert_u(ap, env);
	if (handle_flags_x(env, nb, "0123456789ABCDEF", 1) == 0)
		return (0);
	else if (env->precision == -1 && env->width != -1)
	{
		print_width(nb, env);
		ft_puthexa(nb, "0123456789ABCDEF");
		env->size += ft_size_hexoc(nb, 16);
	}
	else if (env->width == -1 && env->precision != -1)
		env->size += print_precision_x(nb, env, "0123456789ABCDEF");
	else if (env->width != -1 && env->precision != -1)
		print_preciwidth_x(nb, env, "0123456789ABCDEF");
	return (0);
}
