/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 20:54:42 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/30 14:09:38 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_args(t_proc *proc)
{
	if (proc->acb == 0b01000000)
		proc->args[0] = MODA(proc->pc + 2);
	proc->to_inc = 3;
}

void	aff(t_en *e, t_proc *proc)
{
	int	ret;

	(void)e;
	get_args(proc);
	if (is_reg(0, 0, proc->args[0] - 1))
	{
		ret = proc->reg[proc->args[0] - 1] % 256;
		if (ret == 0)
			proc->carry = 1;
		else
			proc->carry = 0;
	}
	else
		proc->carry = 1;
	proc->op = 0;
	proc->pc = MODA(proc->pc + proc->to_inc);
	proc->to_inc = 0;
}
