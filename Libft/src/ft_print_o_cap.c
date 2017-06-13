/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_o_cap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 11:20:57 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/18 17:50:00 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int				print_width_neg_o(unsigned long long nb, t_env *env)
{
	int	size;
	int	width;
	int	i;

	i = 0;
	size = ft_size_hexoc(nb, 8);
	width = env->width - size;
	if (env->flags.hashtag == 1)
		width--;
	while (width > i)
	{
		if (env->flags.neg == 1 || env->zero_width == 0)
			env->size += ft_putchar(' ');
		if (env->flags.neg == 0 && env->zero_width == 1)
			env->size += ft_putchar('0');
		i++;
	}
	return (0);
}

static int		print_width(unsigned long long nb, t_env *env)
{
	int	size;
	int	width;
	int	i;

	i = 0;
	size = ft_size_hexoc(nb, 8);
	width = env->width - size;
	if (env->flags.hashtag == 1)
		width -= 2;
	if (env->flags.hashtag == 1 && nb != 0 && env->flags.zero == 1)
		env->size += ft_putchar('0');
	while (width > i)
	{
		if (env->flags.zero == 0)
			env->size += ft_putchar(' ');
		if (env->flags.zero == 1)
			env->size += ft_putchar('0');
		i++;
	}
	if (env->flags.hashtag == 1 && nb != 0 && env->flags.zero == 0)
		env->size += ft_putchar('0');
	return (0);
}

static int		print_width_precision(int nb, t_env *env)
{
	int	space;
	int	zero;
	int	size;

	zero = 0;
	size = ft_size_hexoc(nb, 8);
	if (env->precision > size)
		zero = env->precision - size;
	if (env->precision == 0 && nb == 0)
		space = env->width;
	else if (zero != 0 && nb >= 0)
		space = env->width - zero - ft_size_hexoc(nb, 8);
	else if (zero == 0 && nb >= 0)
		space = env->width - ft_size_hexoc(nb, 8);
	else
		space = 0;
	ft_print_un(space, zero, env);
	if (env->precision == 0 && nb == 0)
		return (0);
	env->size += ft_size_hexoc(nb, 8);
	if (nb != 0)
		ft_putoctal(nb);
	return (0);
}

static int		print_preciwidth_o(unsigned long long nb, t_env *env)
{
	int	i;
	int	size;
	int j;

	i = 0;
	j = 0;
	size = ft_size_hexoc(nb, 8);
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
			ft_putoctal(nb);
		env->size += ft_size_hexoc(nb, 8);
	}
	return (size);
}

int				ft_print_o_cap(va_list ap, t_env *env)
{
	unsigned long long	nb;

	nb = va_arg(ap, unsigned long);
	if (handle_flags_o(env, nb) == 0)
		return (0);
	else if (env->precision == -1 && env->width != -1)
	{
		print_width(nb, env);
		ft_putoctal(nb);
		env->size += ft_size_hexoc(nb, 8);
	}
	else if (env->width == -1 && env->precision != -1)
		env->size += print_precision_o(nb, env);
	else if (env->width != -1 && env->precision != -1)
		print_preciwidth_o(nb, env);
	return (0);
}
