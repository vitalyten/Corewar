/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 19:50:56 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/26 18:59:12 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_abs(int n)
{
	unsigned int ret;

	ret = (n < 0) ? -n : n;
	return ((int)ret);
}

int		isflag(char c)
{
	return (c == '+' || c == '-' || c == ' ' || c == '#' || c == '0');
}

void	setflags(char *fmt, t_env *env)
{
	while (isflag(fmt[env->i]))
	{
		if (fmt[env->i] == '#')
			env->hash = 1;
		if (fmt[env->i] == '0')
			env->zero = 1;
		if (fmt[env->i] == '-')
			env->minus = 1;
		if (fmt[env->i] == '+')
			env->plus = 1;
		if (fmt[env->i] == ' ')
			env->space = 1;
		env->i++;
	}
	if (fmt[env->i])
		setwidth(fmt, env);
}

int		ft_printf(char *fmt, ...)
{
	t_env	env;

	env.r = 0;
	env.i = 0;
	va_start(env.arg, fmt);
	while (fmt[env.i])
	{
		envreset(&env);
		if (fmt[env.i] == '%' && fmt[env.i + 1])
		{
			env.i++;
			setflags(fmt, &env);
		}
		else if (fmt[env.i] == '%' && !fmt[env.i + 1])
			break ;
		else
		{
			ft_putchar(fmt[env.i]);
			env.r++;
		}
		env.r += env.ret;
		(fmt[env.i]) ? env.i++ : 0;
	}
	va_end(env.arg);
	return (env.r);
}

void	envreset(t_env *env)
{
	env->hash = 0;
	env->zero = 0;
	env->minus = 0;
	env->plus = 0;
	env->space = 0;
	env->none = 0;
	env->width = 0;
	env->prec = -1;
	env->hh = 0;
	env->h = 0;
	env->l = 0;
	env->ll = 0;
	env->j = 0;
	env->z = 0;
	env->ret = 0;
}
