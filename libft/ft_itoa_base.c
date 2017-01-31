/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 20:31:05 by vtenigin          #+#    #+#             */
/*   Updated: 2016/10/08 17:48:25 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_getlen(int n, int base)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n /= base)
		len++;
	return (len);
}

static char		ft_getchar(unsigned int n)
{
	char	*set;

	set = "0123456789ABCDEF";
	return (set[n]);
}

char			*ft_itoa_base(int value, int base)
{
	char			*res;
	int				i;
	int				neg;
	unsigned int	v;

	i = 0;
	neg = 0;
	neg = (value < 0) ? 1 : 0;
	v = (value < 0) ? (unsigned int)-value : (unsigned int)value;
	if (!(res = ft_strnew(ft_getlen(value, base))))
		return (NULL);
	while (v)
	{
		res[i++] = ft_getchar(v % base);
		v /= base;
	}
	if (neg)
		res[i] = '-';
	if (res[0] == 0)
		res[0] = '0';
	return (ft_strrev(res));
}
