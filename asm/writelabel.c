/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writelabel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:18:40 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/11 18:55:02 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		countbytes(t_code *code, int start, int end)
{
	int		ret;
	char	**args;

	// ft_printf("line = %d start = %d end = %d\n", code->i, start, end);
	ret = 0;
	while (code && code->i != start)
		code = code->next;
	while (code && code->label)
	{
		// ft_printf("\n\nline = %d\n", code->op);
		code = code->next;
	}
	while (code && code->i < end)
	{
		ret++;
		if (g_ops[code->op].acb)
			ret++;
		args = code->args;
		while (*args)
		{
			ret++;
			ret += (*args[0] != 'r') ? 1 : 0;
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
	short			sts;
	t_code			*label;
	int				bytes;
	void			*lb;

	step = 0;
	label = env->code;
	while (label)
	{
		if (label->label && !ft_strcmp(arg, label->label))
			break ;
		label = label->next;
	}
	// ft_printf("label id = %d\n", label->i);
	if (label->i < code->i)
	{
		bytes = countbytes(env->code, label->i, code->i);
		step -= bytes;
	}
	else
	{
		bytes = countbytes(env->code, code->i, label->i);
		step += bytes;
	}
	// ft_printf("li = %d line = %d step = %d bytes = %d\n",
	// label->i, code->i, step, bytes);
	sts = (short)step;
	if (size == 4)
		lb = revbytes(&step, size);
	else
		lb = revbytes(&sts, size);
	write(env->fd, lb, size);
	free(lb);
}
