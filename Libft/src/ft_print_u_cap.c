/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_cap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 10:25:02 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/19 13:07:15 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	print_width(unsigned long long nb, t_env *env)
{
	int	size;
	int	width;
	int	i;

	i = 0;
	size = ft_size_unsigned(nb);
	width = env->width - size;
	if (env->flags.zero == 0)
	{
		while (width > i)
		{
			env->size += ft_putchar(' ');
			i++;
		}
	}
	if (env->flags.zero == 1)
	{
		while (width > i)
		{
			env->size += ft_putchar('0');
			i++;
		}
	}
	return (0);
}

static int	get_space(t_env *env, long long nb, int zero)
{
	int	space;

	space = 0;
	if (env->precision == 0 && nb == 0)
		space = env->width;
	else if (zero != 0 && nb >= 0)
		space = env->width - zero - ft_size_unsigned(nb);
	else if (zero == 0 && nb >= 0)
		space = env->width - ft_size_unsigned(nb);
	return (space);
}

static int	print_width_precision(int nb, t_env *env)
{
	int	space;
	int	zero;
	int	size;

	zero = 0;
	size = ft_size_unsigned(nb);
	if (env->precision > size)
		zero = env->precision - size;
	space = get_space(env, nb, zero);
	ft_print_un(space, zero, env);
	if (env->precision == 0 && nb == 0)
		return (0);
	env->size += ft_size_unsigned(nb);
	if (nb != 0)
		ft_putunsigned(nb);
	return (0);
}

static int	print_preciwidth_u(unsigned long long nb, t_env *env)
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
			ft_putunsigned(nb);
		env->size += ft_size_unsigned(nb);
	}
	return (size);
}

int			ft_print_u_cap(va_list ap, t_env *env)
{
	unsigned long long	nb;

	nb = va_arg(ap, unsigned long long);
	if (env->flags.neg == 1)
	{
		ft_putunsigned_cap(nb);
		print_width(nb, env);
		env->size += ft_size_unsigned(nb);
		return (0);
	}
	if (env->width == -1 && env->precision == -1)
	{
		ft_putunsigned_cap(nb);
		env->size += ft_size_unsigned(nb);
	}
	else if (env->width != -1 && env->precision == -1)
	{
		print_width(nb, env);
		env->size += ft_size_unsigned(nb);
		ft_putunsigned_cap(nb);
	}
	else if (env->width != -1 && env->precision != -1)
		print_preciwidth_u(nb, env);
	return (0);
}
