/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 16:01:24 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/07 15:41:32 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;
	unsigned int length;

	i = 0;
	length = (unsigned int)ft_strlen(src);
	while (i < n)
	{
		if (i < length)
		{
			dest[i] = src[i];
		}
		else
			dest[i] = '\0';
		i += 1;
	}
	return (dest);
}
