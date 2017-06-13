/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d_cap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 11:15:59 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/17 18:43:24 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void			ft_norme_width(t_env *env, long long nb, int i, int size)
{
	int	width;

	width = env->width - size;
	if (env->flags.zero == 0 || (env->flags.zero == 1 && env->flags.neg == 1))
	{
		while (width >= i)
		{
			env->size += ft_putchar(' ');
			i++;
		}
		if (env->flags.neg != 1)
			ft_putnbr(nb);
	}
	else if (env->flags.zero == 1 && nb < 0 && env->flags.neg != 1)
	{
		env->size += ft_putchar('-');
		while (width >= i)
		{
			env->size += ft_putchar('0');
			i++;
		}
		nb = -nb;
		ft_putnbr(nb);
		env->size--;
	}
}

static int			print_width(long long nb, t_env *env)
{
	int	size;
	int width;
	int	i;

	size = ft_size_nbr(nb) + env->flags.space;
	width = 0;
	i = 1;
	if (ft_size_nbr(nb) < env->precision && env->flags.neg == 1)
		env->width--;
	if (env->flags.zero == 0 || (env->flags.zero == 1 && env->flags.neg == 1) ||
	(env->flags.zero == 1 && nb < 0 && env->flags.neg != 1))
		ft_norme_width(env, nb, i, size);
	else if (env->flags.zero == 1 && env->flags.neg != 1)
	{
		width = env->width - size - env->flags.pos;
		while (width >= i)
		{
			env->size += ft_putchar('0');
			i++;
		}
		ft_putnbr(nb);
	}
	return (width);
}

static long long	ft_handle_flags(long long nb, t_env *env)
{
	if (env->flags.pos == 1 && nb >= 0 && env->precision == -1)
		env->size += ft_putchar('+');
	if (env->flags.space == 1)
	{
		if (nb >= 0 && env->flags.pos == 0)
			env->size += ft_putchar(' ');
		if (nb < 0)
		{
			env->size += ft_putchar('-');
			nb = -nb;
		}
	}
	return (nb);
}

int					ft_print_d_cap(va_list ap, t_env *env)
{
	long long	nb;

	nb = va_arg(ap, long);
	if (env->flags.neg == 1)
	{
		env->size += print_precision_di(nb, env);
		print_width(nb, env);
		return (0);
	}
	nb = ft_handle_flags(nb, env);
	if (env->width == -1 && env->precision == -1)
	{
		ft_putnbr(nb);
		env->size += ft_size_nbr(nb);
	}
	else if (env->width != -1 && env->precision == -1)
	{
		print_width(nb, env);
		env->size += ft_size_nbr(nb);
	}
	else if (env->width == -1 && env->precision != -1 && nb != 0)
		env->size += print_precision_di(nb, env);
	else if (env->width != -1 && env->precision != -1)
		print_preciwidth_di(nb, env);
	return (0);
}
