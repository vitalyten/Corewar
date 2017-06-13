/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 14:10:14 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/18 17:48:23 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	print_precision_o(unsigned int nb, t_env *env)
{
	int	size;
	int	precision;
	int	ret;

	if (nb == 0 && env->flags.hashtag != 1)
		return (0);
	ret = 0;
	precision = env->precision;
	size = ft_size_hexoc(nb, 8);
	ret += size;
	while (size < precision)
	{
		ft_putchar('0');
		size++;
		ret++;
		if (env->width >= 0)
			env->width--;
	}
	ft_putoctal(nb);
	return (ret);
}

int	print_precision_x(unsigned long long nb, t_env *env, const char *base)
{
	int	size;
	int	precision;
	int	ret;

	if (nb == 0)
		return (0);
	ret = 0;
	size = ft_size_hexoc(nb, 16);
	precision = env->precision;
	while (size <= precision)
	{
		ft_putchar('0');
		size++;
		ret++;
	}
	ft_puthexa(nb, base);
	ret += ft_size_hexoc(nb, 16);
	return (ret);
}

int	print_precision_s(char *str, t_env *env)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(str);
	if ((env->width != -1 && env->flags.neg == 0))
		print_width_str(str, env);
	if (size > env->precision)
	{
		while (i != env->precision)
		{
			ft_putchar(str[i]);
			i++;
		}
	}
	else
	{
		ft_putstr(str);
		return (size);
	}
	if (env->flags.neg == 1)
		print_width_str(str, env);
	return (i);
}

int	print_precision_u(unsigned long long nb, t_env *env)
{
	int	size;
	int	precision;
	int ret;

	ret = 0;
	precision = env->precision;
	if (nb == 0 && precision == 0)
		return (ret);
	size = ft_size_unsigned(nb);
	ret += size;
	while (size < precision)
	{
		ft_putchar('0');
		size++;
		ret++;
	}
	ft_putunsigned(nb);
	return (ret);
}

int	print_precision_di(long long nb, t_env *env)
{
	int	size;
	int ret;

	ret = 0;
	if (env->flags.pos == 1 && nb > 0)
	{
		env->size += ft_putchar('+');
		env->width--;
	}
	size = ft_size_nbr(nb);
	if (nb < 0)
		ft_putchar('-');
	if (nb < 0)
	{
		nb = -nb;
		env->precision++;
	}
	while (size < env->precision)
	{
		ft_putchar('0');
		size++;
	}
	ret += size;
	ft_putnbr(nb);
	return (ret);
}
