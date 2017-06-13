/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:33:31 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/30 21:24:04 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static int	get_and2(t_en *e, t_proc *proc)
{
	int	ret;

	ret = 0;
	if (proc->acb == DIR)
		ret = proc->args[0] &
			fill_reg(e->memory[MODA(proc->pc + proc->args[1])]);
	else if (proc->acb == RDR && is_reg(proc->args[0] - 1, 0, 0))
		ret = proc->reg[proc->args[0] - 1] & proc->args[1];
	else if (proc->acb == IDR)
		ret = fill_reg(e->memory[MODA(proc->pc + proc->args[0])]) &
			proc->args[1];
	else if (proc->acb == DDR)
		ret = proc->args[0] & proc->args[1];
	return (ret);
}

static int	get_and(t_en *e, t_proc *proc)
{
	int	ret;

	ret = 0;
	if (proc->acb == RRR && is_reg(proc->args[0] - 1, proc->args[1] - 1, 0))
		ret = proc->reg[proc->args[0] - 1] & proc->reg[proc->args[1] - 1];
	else if (proc->acb == IRR && is_reg(0, proc->args[1] - 1, 0))
		ret = fill_reg(e->memory[MODA(proc->pc + proc->args[0])]) &
			proc->reg[proc->args[1] - 1];
	else if (proc->acb == DRR && is_reg(0, proc->args[1] - 1, 0))
		ret = proc->args[0] & proc->reg[proc->args[1] - 1];
	else if (proc->acb == RIR && is_reg(proc->args[0], 0, 0))
		ret = proc->reg[proc->args[0] - 1] &
			fill_reg(e->memory[MODA(proc->pc + proc->args[1])]);
	else if (proc->acb == IIR)
		ret = fill_reg(e->memory[MODA(proc->pc + proc->args[0])]) &
			fill_reg(e->memory[MODA(proc->pc + proc->args[1])]);
	else
		ret = get_and2(e, proc);
	return (ret);
}

void		ft_and(t_en *e, t_proc *proc)
{
	int	res;

	get_args_axo(e, proc);
	res = get_and(e, proc);
	if (res == 0)
		proc->carry = 1;
	else if (is_reg(0, 0, proc->args[2] - 1))
	{
		proc->carry = 0;
		proc->reg[proc->args[2] - 1] = res;
	}
	else
		proc->carry = 1;
	proc->pc = MODA(proc->pc + proc->to_inc);
	proc->to_inc = 1;
	proc->op = 0;
}
