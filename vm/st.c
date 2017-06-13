/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 16:20:27 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/30 15:40:18 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	get_args(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b01010000)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = MODR(e->memory[MODA(proc->pc + 3)]);
		proc->to_inc = 4;
	}
	else if (proc->acb == 0b01110000)
	{
		proc->args[0] = e->memory[MODA(proc->pc + 2)];
		proc->args[1] = (get_hex_sum((e->memory[MODA(proc->pc + 3)]),
		(e->memory[MODA(proc->pc + 4)])));
		proc->to_inc = 5;
	}
}

static void	fill_memory(t_en *e, unsigned int adress, int *tab, t_proc *proc)
{
	e->memory[MODA(tab[3])] = proc->reg[proc->args[0] - 1];
	e->memory[MODA(tab[2])] = proc->reg[proc->args[0] - 1] >> 8;
	e->memory[MODA(tab[1])] = proc->reg[proc->args[0] - 1] >> 16;
	e->memory[MODA(adress)] = proc->reg[proc->args[0] - 1] >> 24;
	e->color[MODA(tab[3])] = proc->color;
	e->color[MODA(tab[2])] = proc->color;
	e->color[MODA(tab[1])] = proc->color;
	e->color[MODA(adress)] = proc->color;
}

void		st(t_en *e, t_proc *proc)
{
	unsigned int	adress;
	int				tab[4];
	int				i;

	i = -1;
	get_args(e, proc);
	e->color[proc->pc] = proc->color;
	adress = get_address(proc->pc, proc->args[1]);
	proc->carry = 0;
	while (i++ < 4)
		tab[i] = MODA(adress + i);
	if (adress == 0)
		proc->carry = 1;
	else if (proc->acb == 0b01010000 &&
		is_reg(proc->args[1] - 1, proc->args[0] - 1, 0))
		proc->reg[proc->args[1]] = proc->reg[proc->args[0]];
	else if (proc->acb == 0b01110000)
		fill_memory(e, adress, tab, proc);
	else
		proc->carry = 1;
	proc->pc = MODA(proc->pc + proc->to_inc);
	proc->to_inc = 1;
	proc->op = 0;
}
