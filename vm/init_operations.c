/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 15:33:38 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/29 23:01:56 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		op_norm2(t_en *e, t_proc *proc, int error)
{
	if (proc->op > 0 && g_ops[proc->op - 1].acb)
	{
		if (validacb(e, proc))
			;
		else
			error = 1;
	}
	if (!error)
		operation(e, proc);
	else
	{
		proc->op = 0;
		proc->to_wait = 1;
		proc->pc = MODA(proc->pc + 1);
	}
}

void		op_norm(t_en *e, t_proc *proc, int error)
{
	if (proc->to_wait == 0)
	{
		proc->acb = e->memory[MODA(proc->pc + 1)];
		if (proc->op >= 0 && proc->op <= 16)
			op_norm2(e, proc, error);
		else
		{
			proc->op = 0;
			proc->to_wait = 1;
			proc->pc = MODA(proc->pc + 1);
		}
	}
}

void		init_operation(t_en *e, t_proc *proc)
{
	int	error;

	error = 0;
	if (proc->alive == 1)
	{
		if (proc->op <= 0)
			get_op(e, proc);
		if (proc->op != -1)
		{
			proc->to_wait--;
			op_norm(e, proc, error);
		}
		else if (proc->op == -1)
			proc->pc = MODA(proc->pc + 1);
	}
}
