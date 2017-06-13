/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 10:59:09 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/17 14:39:22 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	add_flag(t_env *env, char value)
{
	if (value == ' ')
		env->flags.space = 1;
	else if (value == '#')
		env->flags.hashtag = 1;
	else if (value == '-')
		env->flags.neg = 1;
	else if (value == '+')
		env->flags.pos = 1;
	else if (value == '0')
		env->flags.zero = 1;
	else
		return ;
}

int		check_flag(char c)
{
	const char	*flags;
	int			i;

	i = 0;
	flags = "#-+0 ";
	while (flags[i])
	{
		if (c == flags[i])
			return (1);
		i++;
	}
	return (0);
}
