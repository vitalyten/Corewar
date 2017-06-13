/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_operation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 21:36:37 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/15 22:55:04 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int	fill_reg(int nb)
{
	int i;
	int	ret;

	i = -1;
	ret = 0;
	if (nb > 32767)
	{
		while (i++ < 2)
		{
			ret += 0xff;
			ret <<= 8;
		}
		ret <<= 8;
		ret += nb;
	}
	else
		return (nb);
	return (ret);
}

int	get_hex_sum1(int hex1, int hex2, int hex3, int hex4)
{
	int res;

	hex1 <<= 8 * 3;
	hex2 <<= 8 * 2;
	hex3 <<= 8;
	res = hex1 + hex2 + hex3 + hex4;
	return (res);
}

int	get_hex_sum(int hex1, int hex2)
{
	int res;

	hex1 <<= 8;
	res = hex1 + hex2;
	return (res);
}
