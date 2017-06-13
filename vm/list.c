/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 20:44:14 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/22 09:24:36 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	add_proc(t_en *e, t_proc *proc, t_proc *new)
{
	t_proc	*tmp;

	(void)proc;
	tmp = e->proc;
	if (tmp->next == tmp)
	{
		e->nb_proc++;
		tmp->next = new;
		new->next = tmp;
		e->end = new;
	}
	else
	{
		e->nb_proc++;
		e->end->next = new;
		e->end = e->end->next;
		e->end->next = e->proc;
	}
}

char	*find_name(int id, t_en *e)
{
	t_champ	*tmp;

	tmp = e->champ;
	while (tmp && id != tmp->id)
		tmp = tmp->next;
	if (!tmp)
		return ("Wrong winner name");
	return (tmp->name);
}
