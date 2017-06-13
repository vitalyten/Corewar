/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:32:12 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/17 14:53:19 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	get_space_di(t_env *env, long long nb, int zero)
{
	int	space;

	space = 0;
	if (env->precision == 0 && nb == 0)
		space = env->width;
	else if (zero != 0 && nb >= 0)
		space = env->width - zero - ft_size_abs(nb);
	else if (zero != 0 && nb < 0)
		space = env->width - zero - ft_size_nbr(nb);
	else if (zero == 0 && nb >= 0)
		space = env->width - ft_size_abs(nb);
	else if (zero == 0 && nb < 0)
		space = env->width - ft_size_nbr(nb);
	if (env->flags.space == 1 || (env->flags.pos == 1 && nb >= 0))
		space--;
	return (space);
}

int	get_width(const char *format, int i, t_env *env)
{
	int	width;

	if (format[i] == '0')
		env->zero_width = 1;
	width = ft_atoi(&format[i]);
	while (ft_isdigit(format[i]))
		i++;
	i--;
	env->width = width;
	return (i);
}
