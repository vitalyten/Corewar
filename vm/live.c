/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 20:32:13 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/29 23:01:41 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	get_args(t_en *e, t_proc *proc)
{
	proc->args[0] = (get_hex_sum1(e->memory[MODA(proc->pc + 1)],
	e->memory[MODA(proc->pc + 2)], e->memory[MODA(proc->pc + 3)],
	e->memory[MODA(proc->pc + 4)]));
}

void		live(t_en *e, t_proc *proc)
{
	int	id;

	get_args(e, proc);
	id = proc->args[0];
	if (id && id < 5 && id > -5)
	{
		if (id < 0 && id > -5)
			e->last_rapported = id;
		e->lives++;
		proc->live++;
		proc->pc = MODA(proc->pc + 5);
	}
	else
		proc->pc = MODA(proc->pc + 5);
	proc->op = 0;
}
