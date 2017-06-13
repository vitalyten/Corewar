/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoctal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 21:19:26 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/19 12:03:27 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_putoctal(unsigned long long nb)
{
	size_t		beg;
	size_t		end;
	const char	*base;

	base = "01234567";
	end = nb % 8;
	beg = (nb - end) / 8;
	if (beg)
		ft_putoctal(beg);
	ft_putchar(base[end]);
}
