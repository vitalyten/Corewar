/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:33:20 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/04 16:19:29 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	get_precision(const char *format, int i, t_env *env)
{
	int	precision;
	int	j;

	precision = 0;
	if (ft_isdigit(format[i]) == 0)
	{
		env->precision = 0;
		return (i - 1);
	}
	while (ft_isdigit(format[i]))
		i++;
	i--;
	j = i;
	while (format[i] != '.')
	{
		if (format[i] != '.')
		{
			precision = ft_atoi(&format[i]);
			i--;
		}
	}
	env->precision = precision;
	return (j);
}

int	get_precision_star(t_env *env, va_list ap)
{
	int	precision;
	int	ret;

	precision = va_arg(ap, int);
	ret = ft_size_nbr(precision);
	env->precision = precision;
	return (ret);
}
