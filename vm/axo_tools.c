/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axo_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 20:21:38 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/30 17:53:02 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_args_axo4(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b10100100)
	{
		proc->args[0] = MODR(get_hex_sum1(e->memory[MODA(proc->pc + 2)],
		e->memory[MODA(proc->pc + 3)], e->memory[MODA(proc->pc + 4)],
		e->memory[MODA(proc->pc + 5)]));
		proc->args[1] = MODR(get_hex_sum1(e->memory[MODA(proc->pc + 2)],
		e->memory[MODA(proc->pc + 3)], e->memory[MODA(proc->pc + 4)],
		e->memory[MODA(proc->pc + 5)]));
		proc->args[2] = MODA(e->memory[proc->pc + 7]);
		proc->to_inc = 8;
	}
}

void	get_args_axo3(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b01100100)
	{
		proc->args[0] = MODA(e->memory[proc->pc + 2]);
		proc->args[1] = MODR(get_hex_sum1(e->memory[MODA(proc->pc + 3)],
			e->memory[MODA(proc->pc + 4)], e->memory[MODA(proc->pc + 5)],
			e->memory[MODA(proc->pc + 6)]));
		proc->args[2] = MODA(e->memory[proc->pc + 7]);
		proc->to_inc = 8;
	}
	else if (proc->acb == 0b11100100)
	{
		proc->args[0] = MODR(get_hex_sum(MODA(e->memory[proc->pc + 2]),
		MODA(e->memory[proc->pc + 3])));
		proc->args[1] = MODR(get_hex_sum1(e->memory[MODA(proc->pc + 4)],
			e->memory[MODA(proc->pc + 5)], e->memory[MODA(proc->pc + 6)],
			e->memory[MODA(proc->pc + 7)]));
		proc->args[2] = MODA(e->memory[proc->pc + 8]);
		proc->to_inc = 9;
	}
	else
		get_args_axo4(e, proc);
}

void	get_args_axo2(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b11110100)
	{
		proc->args[0] = MODR(get_hex_sum(MODA(e->memory[proc->pc + 2]),
		MODA(e->memory[proc->pc + 3])));
		proc->args[1] = MODR(get_hex_sum(MODA(e->memory[proc->pc + 4]),
		MODA(e->memory[proc->pc + 5])));
		proc->args[2] = MODA(e->memory[proc->pc + 6]);
		proc->to_inc = 7;
	}
	else if (proc->acb == 0b10110100)
	{
		proc->args[0] = MODR(get_hex_sum1(e->memory[MODA(proc->pc + 2)],
			e->memory[MODA(proc->pc + 3)], e->memory[MODA(proc->pc + 4)],
			e->memory[MODA(proc->pc + 5)]));
		proc->args[1] = MODR(get_hex_sum(MODA(e->memory[proc->pc + 6]),
		MODA(e->memory[proc->pc + 7])));
		proc->args[2] = MODA(e->memory[proc->pc + 8]);
		proc->to_inc = 9;
	}
	else
		get_args_axo3(e, proc);
}

void	get_args_axo1(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b10010100)
	{
		proc->args[0] = MODR(get_hex_sum1(e->memory[MODA(proc->pc + 2)],
			e->memory[MODA(proc->pc + 3)], e->memory[MODA(proc->pc + 4)],
			e->memory[MODA(proc->pc + 5)]));
		proc->args[1] = MODA(e->memory[proc->pc + 6]);
		proc->args[2] = MODA(e->memory[proc->pc + 7]);
		proc->to_inc = 8;
	}
	else if (proc->acb == 0b01110100)
	{
		proc->args[0] = MODA(e->memory[proc->pc + 2]);
		proc->args[1] = MODR(get_hex_sum(MODA(e->memory[proc->pc + 3]),
		MODA(e->memory[proc->pc + 4])));
		proc->args[2] = MODA(e->memory[proc->pc + 5]);
		proc->to_inc = 6;
	}
	else
		get_args_axo2(e, proc);
}

void	get_args_axo(t_en *e, t_proc *proc)
{
	if (proc->acb == 0b01010100)
	{
		proc->args[0] = MODA(e->memory[proc->pc + 2]);
		proc->args[1] = MODA(e->memory[proc->pc + 3]);
		proc->args[2] = MODA(e->memory[proc->pc + 4]);
		proc->to_inc = 5;
	}
	else if (proc->acb == 0b11010100)
	{
		proc->args[0] = MODR(get_hex_sum(MODA(e->memory[proc->pc + 2]),
		MODA(e->memory[proc->pc + 3])));
		proc->args[1] = MODA(e->memory[proc->pc + 4]);
		proc->args[2] = MODA(e->memory[proc->pc + 5]);
		proc->to_inc = 6;
	}
	else
		get_args_axo1(e, proc);
}
