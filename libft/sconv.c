/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sconv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 22:05:53 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/26 18:09:19 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	slsconv(char type, t_env *env)
{
	if (type == 'S' || env->l)
		lsconv(env);
	else
		sconv(env);
}

void	fillstr(char *str, t_env *env)
{
	int	i;

	i = ft_strlen(str);
	env->ret = (env->prec == -1 || env->prec > i) ? i : env->prec;
	while (env->ret < env->width)
	{
		if (env->minus)
			str = sjoinfree(str, ft_strdup(" "));
		else if (env->zero)
			str = sjoinfree(ft_strdup("0"), str);
		else
			str = sjoinfree(ft_strdup(" "), str);
		env->ret++;
	}
	i = 0;
	if (env->prec == -1)
		ft_putstr(str);
	else
		while ((i < env->prec || i < env->width) && str[i])
			ft_putchar(str[i++]);
	ft_strdel(&str);
}

void	lsconv(t_env *env)
{
	wchar_t *ucs;
	char	*str;
	char	*temp;

	str = ft_strnew(0);
	if (env->prec == 0)
		temp = ft_strnew(0);
	else if (!(ucs = va_arg(env->arg, wchar_t *)))
		temp = ft_strdup("(null)");
	else
		temp = ucstostr(ucs);
	if (env->prec > 0)
	{
		str = snjoinfree(str, temp, env->prec);
		trimucs(str);
	}
	else
		str = sjoinfree(str, temp);
	fillstr(str, env);
}

void	sconv(t_env *env)
{
	char	*str;
	char	*temp;

	str = ft_strnew(0);
	if (env->prec == 0)
		temp = ft_strnew(0);
	else if (!(temp = va_arg(env->arg, char *)))
		temp = ft_strdup("(null)");
	else
		temp = ft_strdup(temp);
	str = (env->prec > 0) ? snjoinfree(str, temp, env->prec)
		: sjoinfree(str, temp);
	fillstr(str, env);
}
