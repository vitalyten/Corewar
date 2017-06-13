/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:31:01 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/30 16:07:37 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		nothing(t_en *e, t_proc *proc)
{
	(void)e;
	proc->pc = MODA(proc->pc + 1);
	if (proc->pc == 4096)
		proc->pc = 0;
}

void		get_op(t_en *e, t_proc *proc)
{
	if (e->memory[proc->pc] && e->memory[proc->pc] < 0x11)
	{
		proc->op = e->memory[proc->pc];
		proc->to_wait = g_ops[proc->op - 1].ncycles;
	}
	else if (e->memory[proc->pc] && e->memory[proc->pc] > 0x11)
	{
		proc->to_wait = 1;
		proc->op = -1;
	}
	else
	{
		proc->op = 0;
		proc->to_wait = 1;
	}
}

void		ft_init_op(void (**operation_type)(t_en *e, t_proc *proc))
{
	operation_type[0] = nothing;
	operation_type[1] = live;
	operation_type[2] = ld;
	operation_type[3] = st;
	operation_type[4] = add;
	operation_type[5] = sub;
	operation_type[6] = ft_and;
	operation_type[7] = ft_or;
	operation_type[8] = ft_xor;
	operation_type[9] = zjmp;
	operation_type[10] = ft_ldi;
	operation_type[11] = sti;
	operation_type[12] = ft_fork;
	operation_type[13] = lld;
	operation_type[14] = ft_lldi;
	operation_type[15] = lfork;
	operation_type[16] = aff;
}

void		operation(t_en *e, t_proc *proc)
{
	void	(*operation_type[17])(t_en *e, t_proc *proc);

	ft_init_op(operation_type);
	operation_type[proc->op](e, proc);
}
