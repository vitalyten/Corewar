/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 15:25:08 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/20 21:34:45 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	showerr(char *msg)
{
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	envinit(t_en *env)
{
	int	i;

	i = -1;
	env->dump = 0;
	env->proc = NULL;
	env->champ = NULL;
	env->end = NULL;
	env->champnb = 0;
	env->nb_cycles = 0;
	env->nb_proc = 0;
	env->lives = 0;
	env->nb_check = 0;
	env->ch = 0;
	env->id_champ = -1;
	env->tot_cycle = 0;
	env->last_rapported = -1;
	env->start = 1;
	env->ch = 1;
	env->die_cycle = CYCLE_TO_DIE;
	while (i++ < 4)
		env->assigned_table[i] = 0;
	ft_bzero(env->memory, MEM_SIZE);
	ft_bzero(env->color_print, MEM_SIZE);
	ft_bzero(env->color, MEM_SIZE);
}

t_proc	*procinit(t_champ *champ, t_en *e)
{
	t_proc	*proc;

	if (!(proc = (t_proc *)malloc(sizeof(t_proc))))
		return (NULL);
	proc->pc = champ->pos;
	proc->start = 0;
	proc->color = champ->color;
	e->nb_proc++;
	proc->champ_id = champ->id;
	proc->carry = 0;
	proc->live = 0;
	proc->alive = 1;
	proc->cycles = 0;
	proc->op = 0;
	proc->acb = 0;
	proc->to_wait = 0;
	proc->to_inc = 1;
	ft_bzero(proc->args, sizeof(int) * MAX_ARGS_NUMBER);
	ft_bzero(proc->reg, sizeof(int) * REG_NUMBER);
	if (champ->id)
		proc->reg[0] = champ->id;
	else
		proc->reg[0] = champ->color - 30;
	return (proc);
}

void	makeproc(t_en *env)
{
	t_champ	*champ;
	t_proc	*proc;

	champ = env->champ;
	while (champ)
	{
		if (env->proc == NULL)
		{
			proc = procinit(champ, env);
			env->proc = proc;
			env->proc->next = proc;
			env->end = env->proc;
		}
		else
		{
			proc = procinit(champ, env);
			proc->next = env->proc;
			env->proc = proc;
			env->end->next = env->proc;
		}
		champ = champ->next;
	}
	env->proc->start = 1;
}

int		validacb(t_en *env, t_proc *proc)
{
	char	arc[3];
	int		i;

	(void)env;
	i = -1;
	arc[0] = (proc->acb & 0xC0) >> 6;
	arc[1] = (proc->acb & 0x30) >> 4;
	arc[2] = (proc->acb & 0xC) >> 2;
	while (++i < g_ops[proc->op - 1].nargs)
	{
		if (arc[i] == IND_CODE)
			arc[i] = T_IND;
		if ((arc[i] & g_ops[proc->op - 1].args[i]) != arc[i])
			return (0);
	}
	return (1);
}
