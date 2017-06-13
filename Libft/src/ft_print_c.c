/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 20:58:53 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/17 14:52:29 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	print_width(t_env *env)
{
	int	i;

	i = 1;
	while (i < env->width)
	{
		env->size += ft_putchar(' ');
		i++;
	}
}

int		ft_print_c(va_list ap, t_env *env)
{
	char	c;

	c = va_arg(ap, int);
	if (env->width != -1 && env->flags.neg != 1)
		print_width(env);
	env->size += ft_putchar(c);
	if (env->width != -1 && env->flags.neg == 1)
		print_width(env);
	return (0);
}
