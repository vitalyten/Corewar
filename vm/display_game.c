/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 16:05:57 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/30 18:13:30 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	get_color(t_en *e)
{
	t_proc *proc;

	proc = e->proc;
	ft_bzero(e->color_print, MEM_SIZE);
	e->color_print[proc->pc] = proc->color;
	if (proc->next)
		proc = proc->next;
	while (proc != e->proc)
	{
		e->color_print[proc->pc] = proc->color;
		proc = proc->next;
	}
}

void	print_operations(t_en *e)
{
	t_proc	*proc;
	int		i;

	proc = e->proc;
	i = -1;
	if (proc->next)
	{
		if (proc->alive)
		{
			printw("%d cycles to launch %x operation.", proc->to_wait,
			proc->op);
		}
		proc = proc->next;
	}
	while (proc != e->proc)
	{
		if (proc->alive)
		{
			printw("%d cycles to launch %x operation.\n", proc->to_wait,
			proc->op);
		}
		proc = proc->next;
	}
}

void	display_memory(t_en *e)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		get_color(e);
		if (e->color_print[i] > 0)
			attron(A_REVERSE);
		attron(COLOR_PAIR(e->color[i]));
		printw("%02x", 0xFF & e->memory[i]);
		attroff(COLOR_PAIR(e->color[i]));
		if (e->color_print[i] > 0)
			attroff(A_REVERSE);
		printw(" ");
		if ((i + 1) % (128 / 2) == 0)
			printw("\n");
		i++;
	}
	attron(COLOR_PAIR(32));
	printw("\n\nCycle: %-10d Cursors: %-10d Total Number of lives: %d/%-10d \
	Checks: %d/9 > Decrease cycle to die with: %d     \
	Cycles to die: %d/%d\n\n", e->tot_cycle, e->nb_proc, NBR_LIVE, e->lives, \
	e->nb_check, CYCLE_DELTA, e->die_cycle, e->nb_cycles);
	attroff(COLOR_PAIR(32));
}

void	ft_print_bonus(t_en *e)
{
	int i;

	i = 0;
	if (e->ch == 0)
		e->ch = getch();
	while (e->ch != '1' && e->ch != '2' && e->ch != '3' && e->ch != '4'
	&& e->ch != ' ' && e->ch != -1)
		e->ch = getch();
	erase();
	display_memory(e);
	print_operations(e);
	refresh();
	if (e->ch == '1')
		e->ch = 1;
	else if (e->ch == '2')
		e->ch = 5;
	else if (e->ch == '3')
		e->ch = 10;
	else if (e->ch == '4')
		e->ch = 100;
	else if (e->ch == ' ')
		e->ch = -1;
}

void	display_game(t_en *e)
{
	if (e->ch != -1)
		e->ch--;
	if (e->bonus && (e->ch == 0 || e->ch == -1))
		ft_print_bonus(e);
	if (e->dump > 0 && e->dump == e->tot_cycle)
		printmemory(e);
}
