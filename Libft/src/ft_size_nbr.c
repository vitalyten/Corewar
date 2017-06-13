/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 14:47:24 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/18 18:40:16 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_size_bin(unsigned int nb)
{
	size_t	beg;
	size_t	end;
	int		i;

	i = 0;
	end = nb % 2;
	beg = (nb - end) / 2;
	i++;
	while (beg)
	{
		end = beg % 2;
		beg = (beg - end) / 2;
		i++;
	}
	return (i);
}

int	ft_size_hexoc(unsigned long long nb, int base)
{
	size_t	beg;
	size_t	end;
	int		i;

	i = 1;
	end = nb % base;
	beg = (nb - end) / base;
	while (beg)
	{
		end = beg % base;
		beg = (beg - end) / base;
		i++;
	}
	return (i);
}

int	ft_size_nbr(long long n)
{
	long long	ind;
	int			size;

	size = 0;
	if (n < -9223372036854775807)
		return (20);
	if (n >= 0 && n <= 9)
		return (1);
	if (n < 0)
	{
		ind = -n;
		size++;
	}
	else if (n == 0)
		return (1);
	else
		ind = n;
	while (ind > 0)
	{
		ind = ind / 10;
		size++;
	}
	return (size);
}

int	ft_size_abs(long long n)
{
	long long		ind;
	int				size;

	size = 0;
	if (n >= 0 && n <= 9)
		return (1);
	if (n < 0)
		n = -n;
	else if (n == 0)
		return (1);
	ind = n;
	while (ind > 0)
	{
		ind = ind / 10;
		size++;
	}
	return (size);
}

int	ft_size_unsigned(unsigned long long n)
{
	unsigned long long	ind;
	int					size;

	size = 0;
	if (n > 0 && n <= 9)
		return (1);
	else if (n == 0)
		return (1);
	else
		ind = n;
	while (ind > 0)
	{
		ind = ind / 10;
		size++;
	}
	return (size);
}
