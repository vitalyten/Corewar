/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xconv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:51:33 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/26 18:53:42 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	xconv(char type, t_env *env)
{
	unsigned long long	x;
	char				*str;

	x = va_arg(env->arg, unsigned long long);
	if (env->j)
		x = (uintmax_t)x;
	else if (env->l)
		x = (unsigned long)x;
	else if (env->z)
		x = (size_t)x;
	else if (env->h)
		x = (unsigned short)x;
	else if (env->hh)
		x = (unsigned char)x;
	else if (!env->ll)
		x = (unsigned int)x;
	if (env->zero && !env->minus && env->prec == -1)
		str = xconvzero(x, env);
	else
		str = xconvstd(x, env);
	env->ret = ft_strlen(str);
	if (type == 'x')
		str = ft_strtolower(str);
	ft_putstr(str);
	ft_strdel(&str);
}

char	*xconvstd(unsigned long long x, t_env *env)
{
	char	*str;

	str = (env->prec == 0 && x == 0) ? ft_strnew(0) : ft_ulltoa_base(x, 16);
	env->ret = ft_strlen(str);
	while (env->ret < env->prec)
	{
		str = sjoinfree(ft_strdup("0"), str);
		env->ret++;
	}
	if (env->hash && x)
	{
		env->ret += 2;
		str = sjoinfree(ft_strdup("0X"), str);
	}
	while (env->ret++ < env->width)
		str = (env->minus) ? sjoinfree(str, ft_strdup(" "))
		: sjoinfree(ft_strdup(" "), str);
	return (str);
}

char	*xconvzero(unsigned long long x, t_env *env)
{
	char	*str;

	str = ft_ulltoa_base(x, 16);
	env->ret = ft_strlen(str);
	if (env->hash && x)
	{
		while (env->ret < env->width - 2)
		{
			str = sjoinfree(ft_strdup("0"), str);
			env->ret++;
		}
		str = sjoinfree(ft_strdup("0X"), str);
		env->ret += 2;
	}
	else
		while (env->ret < env->width)
		{
			str = sjoinfree(ft_strdup("0"), str);
			env->ret++;
		}
	return (str);
}
