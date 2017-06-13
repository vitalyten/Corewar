/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 20:34:30 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/17 17:47:18 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			print_width_str(char *str, t_env *env)
{
	int	size;
	int width;
	int	i;

	if (env->precision != -1)
		size = env->precision;
	else
		size = ft_strlen(str);
	width = env->width - size;
	i = 0;
	if (env->width > size)
	{
		while (width > i)
		{
			if (env->zero_width == 0)
				env->size += ft_putchar(' ');
			if (env->zero_width == 1)
				env->size += ft_putchar('0');
			i++;
		}
	}
	return (width);
}

static int	ft_width_empty(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->width)
	{
		env->size += ft_putchar(' ');
		i++;
	}
	return (0);
}

int			ft_handle_neg(char *str, t_env *env)
{
	env->size += ft_putstr(str);
	print_width_str(str, env);
	return (0);
}

int			ft_print_s(va_list ap, t_env *env)
{
	int		ret;
	char	*str;

	str = va_arg(ap, char *);
	ret = 0;
	if (env->flags.neg == 1 && env->precision == -1)
		return (ft_handle_neg(str, env));
	if (!(str))
	{
		env->size += ft_putstr("(null)");
		return (ret);
	}
	if (env->width != -1 && env->precision == -1)
		ret = print_width_str(str, env);
	if (env->precision == -1)
	{
		ret = ft_putstr(str);
		env->size += ret;
		return (ret);
	}
	if (str[0] == '\0' && env->width != -1)
		return (ft_width_empty(env));
	env->size += print_precision_s(str, env);
	return (ret);
}
