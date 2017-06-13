/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 10:06:26 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/12 10:34:24 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	unsigned int	ind;
	int				size;

	size = 0;
	if (n < 0)
		ind = -n;
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

static int	ft_absolu(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	ft_sign(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char		*ft_itoa(int n)
{
	int		nb_len;
	int		sign;
	char	*str;

	str = NULL;
	nb_len = ft_size(n);
	sign = ft_sign(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char *)malloc(sizeof(char) * (nb_len + sign + 1));
	if (str)
	{
		str = str + sign + nb_len;
		*str = '\0';
		if (!n)
			*--str = '0';
		while (n != 0)
		{
			*--str = ft_absolu(n % 10) + '0';
			n /= 10;
		}
		if (sign)
			*--str = '-';
	}
	return (str);
}
