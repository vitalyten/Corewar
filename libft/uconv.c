/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uconv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:52:12 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/26 18:53:15 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	uconv(char type, t_env *env)
{
	unsigned long long	u;
	char				*str;

	u = va_arg(env->arg, unsigned long long);
	if (env->j)
		u = (uintmax_t)u;
	else if (env->l || type == 'U')
		u = (unsigned long)u;
	else if (env->z)
		u = (size_t)u;
	else if (env->h)
		u = (unsigned short)u;
	else if (env->hh)
		u = (unsigned char)u;
	else if (!env->ll)
		u = (unsigned int)u;
	if (env->zero && !env->minus && env->prec == -1)
		str = uconvzero(u, env);
	else
		str = uconvstd(u, env);
	env->ret = ft_strlen(str);
	ft_putstr(str);
	ft_strdel(&str);
}

char	*uconvstd(unsigned long long u, t_env *env)
{
	char	*str;

	str = (env->prec == 0 && u == 0) ? ft_strnew(0) : ft_ulltoa_base(u, 10);
	env->ret = ft_strlen(str);
	while (env->ret < env->prec)
	{
		str = sjoinfree(ft_strdup("0"), str);
		env->ret++;
	}
	while (env->ret++ < env->width)
		str = (env->minus) ? sjoinfree(str, ft_strdup(" "))
		: sjoinfree(ft_strdup(" "), str);
	return (str);
}

char	*uconvzero(unsigned long long u, t_env *env)
{
	char	*str;

	str = ft_ulltoa_base(u, 10);
	env->ret = ft_strlen(str);
	while (env->ret < env->prec || env->ret < env->width)
	{
		str = sjoinfree(ft_strdup("0"), str);
		env->ret++;
	}
	return (str);
}
