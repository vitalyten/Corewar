/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oconv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:53:18 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/26 18:52:39 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	oconv(char type, t_env *env)
{
	unsigned long long	o;
	char				*str;

	o = va_arg(env->arg, unsigned long long);
	if (env->j)
		o = (uintmax_t)o;
	else if (env->l || type == 'O')
		o = (unsigned long)o;
	else if (env->z)
		o = (size_t)o;
	else if (env->h)
		o = (unsigned short)o;
	else if (env->hh)
		o = (unsigned char)o;
	else if (!env->ll)
		o = (unsigned int)o;
	if (env->zero && !env->minus && env->prec == -1)
		str = oconvzero(o, env);
	else
		str = oconvstd(o, env);
	env->ret = ft_strlen(str);
	ft_putstr(str);
	ft_strdel(&str);
}

char	*oconvstd(unsigned long long o, t_env *env)
{
	char	*str;

	str = (env->prec == 0 && o == 0) ? ft_strnew(0) : ft_ulltoa_base(o, 8);
	env->ret = ft_strlen(str);
	while (env->ret < env->prec)
	{
		str = sjoinfree(ft_strdup("0"), str);
		env->ret++;
	}
	if (env->hash && *str != '0')
	{
		env->ret++;
		str = sjoinfree(ft_strdup("0"), str);
	}
	while (env->ret++ < env->width)
		str = (env->minus) ? sjoinfree(str, ft_strdup(" "))
		: sjoinfree(ft_strdup(" "), str);
	return (str);
}

char	*oconvzero(unsigned long long o, t_env *env)
{
	char	*str;

	str = ft_ulltoa_base(o, 8);
	env->ret = ft_strlen(str);
	while (env->ret < env->prec || env->ret < env->width)
	{
		str = sjoinfree(ft_strdup("0"), str);
		env->ret++;
	}
	if (env->hash && *str != '0')
	{
		env->ret++;
		str = sjoinfree(ft_strdup("0"), str);
	}
	return (str);
}
