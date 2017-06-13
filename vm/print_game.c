/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 15:23:28 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/30 18:00:54 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_print_dump_init(t_en *e)
{
	t_champ	*champ;
	int		k;

	k = -1;
	champ = e->champ;
	ft_printf("Introducing contestants...\n");
	while (champ)
	{
		ft_printf("* Player %i, weighing %i bytes, \"%s\" (\"%s\") !\n", \
		-champ->id, champ->size, champ->name, \
		champ->comment);
		champ = champ->next;
	}
}

void	ft_print_normal(t_en *e)
{
	int	i;
	int	hex;

	hex = 0;
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i == 0)
			ft_printf("0x0000 : ");
		if (i > 0 && (i) % (64) == 0)
			ft_printf("0x%04x : ", hex);
		if (e->memory[i])
			ft_printf("%02x ", 0xFF & e->memory[i]);
		else
			ft_printf("00 ");
		if ((i + 1) % (64) == 0)
		{
			ft_printf("\n");
			hex += 64;
		}
		i++;
	}
}

void	printmemory(t_en *env)
{
	ft_print_normal(env);
}
