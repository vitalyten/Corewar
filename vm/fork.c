/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 20:34:20 by vkannema          #+#    #+#             */
/*   Updated: 2017/06/05 14:11:52 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_proc	*newproc(t_proc *proc)
{
	t_proc	*new;
	int		i;

	i = 0;
	new = (t_proc *)malloc(sizeof(t_proc));
	new->color = proc->color;
	new->champ_id = proc->champ_id;
	new->carry = proc->carry;
	new->live = proc->live;
	new->alive = 1;
	new->pc = proc->pc;
	new->cycles = proc->cycles;
	ft_bzero(new->args, sizeof(int) * MAX_ARGS_NUMBER);
	new->acb = 0;
	new->start = 0;
	new->op = 0;
	new->to_inc = 1;
	while (i < REG_NUMBER)
	{
		new->reg[i] = proc->reg[i];
		i++;
	}
	return (new);
}

static short	get_dir(t_en *e, t_proc *proc, int i)
{
	unsigned short	r;

	r = ((e->memory[MODA(proc->pc + i)]) << 8) |
			(e->memory[MODA(proc->pc + i + 1)]);
	return ((short)r);
}

static int		get_fork(int pc, int res)
{
	int	ret;

	ret = 0;
	if (res > 32767)
	{
		ret = -(MODR(res));
		return (pc + ret);
	}
	return (pc + MODR(res));
}

void			ft_fork(t_en *e, t_proc *proc)
{
	t_proc				*new;
	unsigned int		res;

	res = get_dir(e, proc, 1);
	res = get_fork(proc->pc, res);
	res = MODA(res);
	proc->op = 0;
	new = newproc(proc);
	new->pc = res;
	proc->pc = MODA(proc->pc + 3);
	add_proc(e, proc, new);
}
