/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addcode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 20:29:11 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/24 20:29:39 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	addcode(t_en *env, int op, char **args)
{
	t_code *tmp;
	t_code *code;

	tmp = (t_code *)malloc(sizeof(t_code));
	tmp->next = NULL;
	tmp->op = op;
	tmp->args = args;
	tmp->label = NULL;
	if (env->code)
	{
		code = env->code;
		while (code->next)
			code = code->next;
		code->next = tmp;
	}
	else
		env->code = tmp;
}

void	addlabel(t_en *env, char *label)
{
	t_code *tmp;
	t_code *code;

	tmp = (t_code *)malloc(sizeof(t_code));
	tmp->next = NULL;
	tmp->op = -1;
	tmp->args = NULL;
	tmp->label = ft_strdup(label);
	if (env->code)
	{
		code = env->code;
		while (code->next)
			code = code->next;
		code->next = tmp;
	}
	else
		env->code = tmp;
}
