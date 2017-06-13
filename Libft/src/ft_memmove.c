/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:57:28 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/10 11:08:15 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*srce;
	size_t			i;

	i = 0;
	dest = (unsigned char *)dst;
	srce = (unsigned char *)src;
	if (dest > srce)
	{
		while (i < len)
		{
			dest[len - 1] = srce[len - 1];
			len--;
		}
	}
	else
		while (i < len)
		{
			dest[i] = srce[i];
			i++;
		}
	return (dst);
}
