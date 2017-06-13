/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 14:32:20 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/17 14:53:49 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	clean_flags(t_env *env)
{
	env->flags.space = 0;
	env->flags.neg = 0;
	env->flags.pos = 0;
	env->flags.hashtag = 0;
	env->flags.zero = 0;
}

void		clean_env(t_env *env)
{
	clean_flags(env);
	env->flag = 0;
	env->type = 0;
	env->conv = 0;
	env->precision = -1;
	env->width = -1;
	env->zero_width = 0;
	env->modif = 0;
	env->dual = 0;
}
