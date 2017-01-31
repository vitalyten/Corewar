/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toabase.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:00:45 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/26 18:08:30 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ishead(char c)
{
	if ((c & 0xF0) == 0xF0)
		return (4);
	if ((c & 0xE0) == 0xE0)
		return (3);
	if ((c & 0xC0) == 0xc0)
		return (2);
	if (!(c & 0x80))
		return (1);
	return (0);
}

void			trimucs(char *str)
{
	int len;
	int ucl;
	int i;

	len = ft_strlen(str);
	len--;
	while (!(ucl = ishead(str[len])) && len >= 0)
		len--;
	i = 0;
	while (str[len + i])
		i++;
	if (i != ucl)
		str[len] = '\0';
}

unsigned char	atocbin(char *str)
{
	unsigned char	uc;
	int				i;

	uc = 0;
	i = 0;
	while (str[i])
	{
		uc *= 2;
		uc += str[i] - '0';
		i++;
	}
	return (uc);
}

char			*ft_lltoa_base(long long value, int base)
{
	int				mod;
	int				len;
	char			*ret;
	long long		temp;

	if (base < 2 || base > 16)
		return (NULL);
	len = 1;
	temp = value;
	while (temp /= base)
		len++;
	if (!(ret = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ret[len--] = '\0';
	while (len >= 0 && value / base)
	{
		mod = ft_abs(value % base);
		ret[len--] = (mod < 10) ? mod + '0' : mod + '7';
		value /= base;
	}
	mod = ft_abs(value % base);
	ret[len--] = (mod < 10) ? mod + '0' : mod + '7';
	return (ret);
}

char			*ft_ulltoa_base(unsigned long long value, int base)
{
	int					mod;
	int					len;
	char				*ret;
	unsigned long long	temp;

	if (base < 2 || base > 16)
		return (NULL);
	len = 1;
	temp = value;
	while (temp /= base)
		len++;
	if (!(ret = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	ret[len--] = '\0';
	while (len >= 0 && value / base)
	{
		mod = value % base;
		ret[len] = (mod < 10) ? mod + '0' : mod + '7';
		value /= base;
		len--;
	}
	mod = value % base;
	ret[len--] = (mod < 10) ? mod + '0' : mod + '7';
	return (ret);
}
