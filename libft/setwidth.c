/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setwidth.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 20:31:57 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/23 21:40:31 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		iswidth(char c)
{
	return (c == '*' || (c > '0' && c <= '9'));
}

void	setwidth(char *fmt, t_env *env)
{
	while (iswidth(fmt[env->i]))
	{
		if (fmt[env->i] > '0' && fmt[env->i] <= '9')
		{
			env->width = ft_atoi(&fmt[env->i]);
			while (fmt[env->i] >= '0' && fmt[env->i] <= '9')
				env->i++;
		}
		if (fmt[env->i] == '*')
		{
			env->width = va_arg(env->arg, int);
			if (env->width < 0)
			{
				env->minus = 1;
				env->width = ft_abs(env->width);
			}
			env->i++;
		}
	}
	if (fmt[env->i] == '.')
		setprec(fmt, env);
	else if (fmt[env->i])
		setmod(fmt, env);
}

void	setprec(char *fmt, t_env *env)
{
	env->i++;
	if (fmt[env->i] >= '0' && fmt[env->i] <= '9')
	{
		env->prec = ft_atoi(&fmt[env->i]);
		while (fmt[env->i] >= '0' && fmt[env->i] <= '9')
			env->i++;
	}
	else if (fmt[env->i] == '*')
	{
		env->prec = va_arg(env->arg, int);
		if (env->prec < 0)
			env->prec = -1;
		env->i++;
	}
	else
		env->prec = 0;
	if (fmt[env->i] == '.')
		setprec(fmt, env);
	else if (fmt[env->i])
		setmod(fmt, env);
}

int		ismod(char c)
{
	return (c == 'h' || c == 'l' || c == 'j' || c == 'z');
}

void	setmod(char *fmt, t_env *env)
{
	while (ismod(fmt[env->i]))
	{
		if (fmt[env->i] == 'h' && fmt[env->i + 1] == 'h')
			env->hh = 1;
		else if (fmt[env->i] == 'h')
			env->h = 1;
		else if (fmt[env->i] == 'l' && fmt[env->i + 1] == 'l')
			env->ll = 1;
		else if (fmt[env->i] == 'l')
			env->l = 1;
		else if (fmt[env->i] == 'j')
			env->j = 1;
		else if (fmt[env->i] == 'z')
			env->z = 1;
		if ((fmt[env->i] == 'h' && fmt[env->i + 1] == 'h')
			|| (fmt[env->i] == 'l' && fmt[env->i + 1] == 'l'))
			env->i++;
		env->i++;
	}
	if (isflag(fmt[env->i]))
		setflags(fmt, env);
	else if (fmt[env->i])
		settype(fmt, env);
}
