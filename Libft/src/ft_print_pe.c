/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 12:41:38 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/17 14:48:39 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	print_width(t_env *env)
{
	int width;
	int	i;

	width = 0;
	i = 1;
	if (env->width > 1 && env->zero_width == 0)
	{
		width = env->width - 1;
		while (width >= i)
		{
			env->size += ft_putchar(' ');
			i++;
		}
	}
	else if (env->width > 1 && env->zero_width == 1)
	{
		width = env->width - 1;
		while (width >= i)
		{
			env->size += ft_putchar('0');
			i++;
		}
	}
	return (width);
}

int			ft_print_pe(va_list ap, t_env *env)
{
	(void)ap;
	if (env->precision == -1 && env->width == -1)
		env->size += ft_putchar('%');
	else if (env->flags.neg != 1)
	{
		print_width(env);
		env->size += ft_putchar('%');
	}
	else
	{
		env->size += ft_putchar('%');
		print_width(env);
	}
	return (env->size);
}
