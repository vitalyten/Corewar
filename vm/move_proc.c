/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 19:42:05 by vkannema          #+#    #+#             */
/*   Updated: 2017/06/05 14:12:05 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	reset_lives(t_en *e)
{
	t_proc	*tmp;

	tmp = e->proc;
	if (!tmp->live)
		tmp->alive = 0;
	tmp->live = 0;
	tmp = tmp->next;
	while (tmp != e->proc)
	{
		if (!tmp->live)
			tmp->alive = 0;
		tmp->live = 0;
		tmp = tmp->next;
	}
}

void	new_cycle(t_en *e, int *end)
{
	if (e->lives == 0 || (e->die_cycle - CYCLE_DELTA) < 1)
		*end = 0;
	if (e->lives < NBR_LIVE)
		e->nb_check++;
	if (e->nb_check == MAX_CHECKS || e->lives >= NBR_LIVE)
	{
		e->die_cycle -= CYCLE_DELTA;
		if (e->die_cycle < 0)
			e->die_cycle = 0;
		e->nb_check = 0;
	}
	if (e->start == 0)
		reset_lives(e);
	e->start = 0;
	e->lives = 0;
	e->nb_cycles = 0;
}

void	adjust_cycles(t_en *e, int *end)
{
	display_game(e);
	if (e->nb_cycles >= e->die_cycle)
		new_cycle(e, end);
	else
	{
		e->start = 0;
		e->nb_cycles++;
		e->tot_cycle++;
	}
}

void	move_proc(t_en *e)
{
	int		end;
	t_proc	*proc;

	proc = e->proc;
	end = 1;
	e->start = 1;
	if (e->bonus)
		ft_init_ncurses();
	display_game(e);
	while (end)
	{
		if (proc->start == 1)
			adjust_cycles(e, &end);
		if (end)
		{
			if (proc->alive)
				init_operation(e, proc);
		}
		proc = proc->next;
	}
	endwin();
}
