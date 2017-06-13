/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 10:59:58 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/07 11:21:28 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	get_modif(const char *format, int i, t_env *env)
{
	if ((format[i] == 'h' && format[i + 1] == 'h') ||
		(format[i] == 'l' && format[i + 1] == 'l'))
	{
		env->modif = format[i];
		env->dual = 1;
		return (1);
	}
	else if ((format[i] == 'h' && format[i + 1] != 'h')
		|| (format[i] == 'l' && format[i + 1] != 'l'))
	{
		env->modif = format[i];
		env->dual = 0;
		return (0);
	}
	else if (format[i] == 'j' || format[i] == 'z')
	{
		env->modif = format[i];
		return (0);
	}
	return (0);
}
