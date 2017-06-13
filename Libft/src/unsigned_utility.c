/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 12:35:48 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/18 18:14:33 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	print_width_neg(unsigned long long nb, t_env *env, int base)
{
	int	size;
	int	width;
	int	i;

	i = 0;
	size = ft_size_hexoc(nb, base);
	width = env->width - size;
	if (env->flags.hashtag == 1)
		width -= 2;
	while (width > i)
	{
		if (env->zero_width == 0 || env->flags.neg == 1)
			env->size += ft_putchar(' ');
		if (env->zero_width == 1 && env->flags.neg != 1)
			env->size += ft_putchar('0');
		i++;
	}
	return (0);
}

void		ft_print_un(int space, int zero, t_env *env)
{
	int	i;

	i = 0;
	while (i < space)
	{
		env->size += ft_putchar(' ');
		i++;
	}
	i = 0;
	while (i < zero)
	{
		env->size += ft_putchar('0');
		i++;
	}
}

int			handle_flags_x(t_env *env, unsigned long long nb,
	const char *base, int cap)
{
	if (env->flags.neg == 1)
	{
		if (env->flags.hashtag == 1 && cap == 0)
			env->size += ft_putstr("0x");
		if (env->flags.hashtag == 1 && cap == 1)
			env->size += ft_putstr("0X");
		ft_puthexa(nb, base);
		env->size += ft_size_hexoc(nb, 16);
		print_width_neg(nb, env, 16);
		return (0);
	}
	if (env->flags.hashtag == 1 && env->width == -1 && nb != 0)
	{
		if (cap == 0)
			env->size += ft_putstr("0x");
		if (cap == 1)
			env->size += ft_putstr("0X");
	}
	if (env->width == -1 && env->precision == -1)
	{
		env->size += ft_size_hexoc(nb, 16);
		ft_puthexa(nb, base);
	}
	return (1);
}

int			handle_flags_o(t_env *env, unsigned long long nb)
{
	if (env->flags.neg == 1)
	{
		if (env->flags.hashtag == 1)
			env->size += ft_putchar('0');
		env->size += print_precision_o(nb, env);
		print_width_neg_o(nb, env);
		return (0);
	}
	if (env->flags.hashtag == 1 && env->width == -1 && nb != 0)
		env->size += ft_putchar('0');
	if (env->width == -1 && env->precision == -1)
	{
		env->size += ft_size_hexoc(nb, 8);
		ft_putoctal(nb);
	}
	return (1);
}

int			handle_flags_u(t_env *env, unsigned long long nb)
{
	if (env->flags.neg == 1)
	{
		ft_putunsigned(nb);
		print_width_u(nb, env);
		env->size += ft_size_unsigned(nb);
		return (0);
	}
	if (env->width == -1 && env->precision == -1)
	{
		ft_putunsigned(nb);
		env->size += ft_size_unsigned(nb);
	}
	return (1);
}
