/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 11:09:48 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/19 16:33:04 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	get_dump(char *s1, char *s2, t_en *e)
{
	if (!ft_strcmp(s1, "-dump"))
	{
		if (s2 && ft_atoi(s2))
			e->dump = ft_atoi(s2);
		else
			showerr("error -dump");
		return (1);
	}
	return (0);
}

int	get_bonus(char *s, t_en *e)
{
	e->bonus = 0;
	if (ft_strcmp(s, "-i") == 0)
	{
		e->bonus = 1;
		return (1);
	}
	return (0);
}

int	is_assignment(char *s, char *s2, t_en *e)
{
	if (!ft_strcmp(s, "-n"))
	{
		if (ft_atoi(s2) < 0 && ft_atoi(s2) > -5)
		{
			e->is_assignment = 1;
			e->assignement = ft_atoi(s2);
			if (e->assigned_table[-ft_atoi(s2) - 1] == 0)
				e->assigned_table[-ft_atoi(s2) - 1] = 1;
			else
				showerr("no assignement possible");
			return (1);
		}
		showerr("bad -n argument");
	}
	e->is_assignment = 0;
	e->assignement = 0;
	return (0);
}
