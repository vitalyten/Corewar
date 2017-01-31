/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cconv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:55:22 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/26 18:26:14 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	clcconv(char type, t_env *env)
{
	if (type == 'C' || env->l)
		lcconv(env);
	else
		cconv(env);
}

void	lcconv(t_env *env)
{
	unsigned int	c;
	char			*str;
	char			**uc;

	c = va_arg(env->arg, unsigned int);
	str = ft_ulltoa_base(c, 2);
	uc = getunicode(str);
	retcount(uc, env);
	if (env->minus)
		printuc(uc);
	while (env->ret < env->width)
	{
		if (env->zero && !env->minus)
			ft_putchar('0');
		else
			ft_putchar(' ');
		env->ret++;
	}
	if (!env->minus)
		printuc(uc);
	free2d(uc);
}

void	cconv(t_env *env)
{
	char	c;

	env->ret++;
	c = va_arg(env->arg, int);
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

void	free2d(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		ft_strdel(&strs[i]);
		i++;
	}
	free(strs);
}

void	retcount(char **strs, t_env *env)
{
	int				i;

	i = 0;
	while (strs[i++])
		env->ret++;
}
