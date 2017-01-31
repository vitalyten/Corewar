/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settype.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 21:28:31 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/23 21:14:51 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	settype(char *fmt, t_env *env)
{
	if (fmt[env->i] == 's' || fmt[env->i] == 'S')
		slsconv(fmt[env->i], env);
	else if (fmt[env->i] == 'p')
		pconv(env);
	else if (fmt[env->i] == 'd' || fmt[env->i] == 'D' || fmt[env->i] == 'i')
		dconv(fmt[env->i], env);
	else if (fmt[env->i] == 'o' || fmt[env->i] == 'O')
		oconv(fmt[env->i], env);
	else if (fmt[env->i] == 'u' || fmt[env->i] == 'U')
		uconv(fmt[env->i], env);
	else if (fmt[env->i] == 'x' || fmt[env->i] == 'X')
		xconv(fmt[env->i], env);
	else if (fmt[env->i] == 'c' || fmt[env->i] == 'C')
		clcconv(fmt[env->i], env);
	else if (fmt[env->i] == '%')
		percentconv(env);
	else
		invtype(fmt[env->i], env);
}

void	invtype(char c, t_env *env)
{
	env->ret++;
	if (env->minus)
		ft_putchar(c);
	while (env->ret < env->width)
	{
		if (env->zero && !env->minus)
			ft_putchar('0');
		else
			ft_putchar(' ');
		env->ret++;
	}
	if (!env->minus)
		ft_putchar(c);
}
