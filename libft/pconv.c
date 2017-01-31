/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pconv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 15:22:34 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/26 16:16:50 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*sjoinfree(char *s1, char *s2)
{
	char	*ret;

	ret = ft_strjoin(s1, s2);
	if (s1)
		ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
	return (ret);
}

char	*snjoinfree(char *s1, char *s2, size_t len)
{
	char	*ret;

	ret = ft_strnjoin(s1, s2, len);
	if (s1)
		ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
	return (ret);
}

char	*sjfplus(char *s1, char *s2, t_env *env)
{
	char	*ret;

	env->ret++;
	ret = ft_strjoin(s1, s2);
	if (s1)
		ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
	return (ret);
}

void	percentconv(t_env *env)
{
	env->ret = 1;
	if (env->minus)
		ft_putchar('%');
	while (env->ret < env->width)
	{
		(env->zero && !env->minus) ? ft_putchar('0') : ft_putchar(' ');
		env->ret++;
	}
	if (!env->minus)
		ft_putchar('%');
}

void	pconv(t_env *env)
{
	unsigned long long	x;
	char				*str;

	x = va_arg(env->arg, unsigned long long);
	str = (env->prec == 0 && x == 0) ? ft_strnew(0) : ft_ulltoa_base(x, 16);
	env->ret = ft_strlen(str);
	if (env->prec > 0)
		while (env->ret < env->prec)
			str = sjfplus(ft_strdup("0"), str, env);
	else if (env->zero && !env->minus && env->prec && !(!env->prec && !x))
		while (env->ret < env->width - 2)
			str = sjfplus(ft_strdup("0"), str, env);
	env->ret += 2;
	str = sjoinfree(ft_strdup("0X"), str);
	while (env->ret++ < env->width)
		str = (env->minus) ? sjoinfree(str, ft_strdup(" "))
		: sjoinfree(ft_strdup(" "), str);
	str = ft_strtolower(str);
	env->ret = ft_strlen(str);
	ft_putstr(str);
	ft_strdel(&str);
}
