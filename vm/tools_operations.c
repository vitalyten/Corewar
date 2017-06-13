/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 21:30:01 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/30 12:04:29 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			get_address(int pc, int arg)
{
	unsigned int	res;

	if (arg > 32767)
	{
		arg = 0xffff - arg + 1;
		arg = MODR(arg);
		arg = pc - arg;
		res = MODA(arg);
		return (MODA(res));
	}
	arg = MODR(arg);
	return (pc + arg);
}

int			definejump(int acb)
{
	if (acb == 0b01010100)
		return (5);
	else if (acb == 0b01100100 || acb == 0b01110100 || acb == 0b01011000)
		return (6);
	else if (acb == 0b01101000 || acb == 0b01111000)
		return (7);
	return (1);
}

int			is_reg(int a1, int a2, int a3)
{
	if (a1 < 0 || a1 >= REG_NUMBER ||
			a2 < 0 || a2 >= REG_NUMBER ||
				a3 < 0 || a3 >= REG_NUMBER)
		return (0);
	return (1);
}
