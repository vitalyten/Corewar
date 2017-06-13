/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 21:18:52 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/30 12:05:44 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	get_args(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b01010100)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = e->memory[MODA(proc->pc + 3)];
		proc->args[2] = e->memory[MODA(proc->pc + 4)];
		proc->to_inc = 5;
	}
}

void		sub(t_en *e, t_proc *proc)
{
	int	res;

	get_args(e, proc);
	if (is_reg(proc->args[0] - 1, proc->args[1] - 1, proc->args[2] - 1))
	{
		res = proc->reg[proc->args[0] - 1] - proc->reg[proc->args[1] - 1];
		if (res == 0)
		{
			proc->reg[proc->args[2] - 1] = res;
			proc->carry = 1;
			proc->to_inc = 5;
		}
		else
		{
			proc->carry = 0;
			proc->reg[proc->args[2] - 1] = res;
		}
	}
	else
		proc->carry = 0;
	proc->pc = MODA(proc->pc + proc->to_inc);
	proc->to_inc = 1;
	proc->op = 0;
}
