/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writelabel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:18:40 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/13 22:29:29 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		countbytes(t_code *code, int start, int end)
{
	int		ret;
	char	**args;

	ret = 0;
	while (code && code->i != start)
		code = code->next;
	while (code && code->label)
		code = code->next;
	while (code && code->i < end)
	{
		ret++;
		if (g_ops[code->op].acb)
			ret++;
		args = code->args;
		while (*args)
		{
			ret += (*args[0] != 'r') ? 2 : 1;
			ret += (*args[0] == '%' && !g_ops[code->op].index) ? 2 : 0;
			args++;
		}
		code = code->next;
		while (code && code->label)
			code = code->next;
	}
	return (ret);
}

void	writelabel(t_en *env, t_code *code, char *arg, int size)
{
	unsigned int	step;
	t_code			*label;
	void			*lb;

	step = 0;
	label = env->code;
	while (label)
	{
		if (label->label && !ft_strcmp(arg, label->label))
			break ;
		label = label->next;
	}
	if (label->i < code->i)
		step -= countbytes(env->code, label->i, code->i);
	else
		step += countbytes(env->code, code->i, label->i);
	lb = revbytes(&step, size);
	write(env->fd, lb, size);
	free(lb);
}
