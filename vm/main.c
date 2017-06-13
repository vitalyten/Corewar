/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 21:47:53 by vtenigin          #+#    #+#             */
/*   Updated: 2017/05/30 21:24:32 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	winner(t_en *e)
{
	t_champ *champ;

	champ = e->champ;
	while (champ)
	{
		if (champ->id == e->last_rapported)
			ft_printf("Contestant %d, \"%s\", has won !\n",
			-(champ->id), champ->name);
		champ = champ->next;
	}
}

int		main(int ac, char **av)
{
	t_en	env;
	int		i;

	envinit(&env);
	if (ac < 2)
		showerr("usage: ./corewar champ1.cor...");
	i = 0;
	if (get_bonus(av[i + 1], &env))
		i++;
	if (get_dump(av[i + 1], av[i + 2], &env))
		i += 2;
	while (av[++i])
	{
		if (is_assignment(av[i], av[i + 1], &env))
			i += 2;
		readchamp(&env, av[i]);
	}
	writechamp(&env);
	makeproc(&env);
	ft_print_dump_init(&env);
	env.proc->start = 1;
	move_proc(&env);
	winner(&env);
	return (0);
}
