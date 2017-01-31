/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dconv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:54:35 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:22 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dconv(char type, t_env *env)
{
	long long	d;
	char		*str;

	d = va_arg(env->arg, long long);
	if (env->j)
		d = (intmax_t)d;
	else if (env->l || type == 'D')
		d = (long)d;
	else if (env->z)
		d = (size_t)d;
	else if (env->h)
		d = (short)d;
	else if (env->hh)
		d = (signed char)d;
	else if (!env->ll)
		d = (int)d;
	if (env->zero && !env->minus && env->prec == -1)
		str = dconvzero(d, env);
	else
		str = dconvstd(d, env);
	env->ret = ft_strlen(str);
	ft_putstr(str);
	ft_strdel(&str);
}

char	*dconvstd(long long d, t_env *env)
{
	char	*str;

	str = (env->prec == 0 && d == 0) ? ft_strnew(0) : ft_lltoa_base(d, 10);
	env->ret = ft_strlen(str);
	while (env->ret < env->prec)
	{
		str = sjoinfree(ft_strdup("0"), str);
		env->ret++;
	}
	if (d < 0 || env->plus || env->space)
		env->ret++;
	if (env->plus && d >= 0)
		str = sjoinfree(ft_strdup("+"), str);
	if (env->space && d >= 0 && !env->plus)
		str = sjoinfree(ft_strdup(" "), str);
	if (d < 0)
		str = sjoinfree(ft_strdup("-"), str);
	while (env->ret++ < env->width)
		str = (env->minus) ? sjoinfree(str, ft_strdup(" "))
		: sjoinfree(ft_strdup(" "), str);
	return (str);
}

char	*dconvzero(long long d, t_env *env)
{
	char	*str;
	int		len;

	str = ft_lltoa_base(d, 10);
	len = ft_strlen(str);
	env->ret = len;
	if (d < 0 || env->plus || env->space)
		env->ret++;
	while (len++ < env->prec || env->ret++ < env->width)
		str = sjoinfree(ft_strdup("0"), str);
	if (env->plus && d >= 0)
		str = sjoinfree(ft_strdup("+"), str);
	if (env->space && d >= 0)
		str = sjoinfree(ft_strdup(" "), str);
	if (d < 0)
		str = sjoinfree(ft_strdup("-"), str);
	return (str);
}
