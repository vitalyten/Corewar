/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ncurse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 10:58:23 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/14 18:18:52 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_init_ncurses(void)
{
	initscr();
	noecho();
	start_color();
	init_color(COLOR_WHITE, 220, 220, 220);
	init_pair(27, COLOR_YELLOW, COLOR_BLACK);
	init_pair(28, COLOR_BLUE, COLOR_BLACK);
	init_pair(29, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(30, COLOR_CYAN, COLOR_BLACK);
	init_pair(31, COLOR_RED, COLOR_BLACK);
	init_pair(32, COLOR_GREEN, COLOR_BLACK);
	init_pair(33, COLOR_YELLOW, COLOR_BLACK);
	init_pair(34, COLOR_BLACK, COLOR_BLUE);
	init_pair(35, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(36, COLOR_BLACK, COLOR_CYAN);
	init_pair(37, COLOR_BLACK, COLOR_RED);
	init_pair(38, COLOR_BLACK, COLOR_GREEN);
	init_pair(39, COLOR_WHITE, COLOR_BLACK);
	init_pair(40, COLOR_BLACK, COLOR_GREEN);
	init_pair(41, COLOR_GREEN, COLOR_BLACK);
	curs_set(FALSE);
}
