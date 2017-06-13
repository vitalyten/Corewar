/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:43:24 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/10 11:34:29 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	size_t			i;
	unsigned char	*mem;

	mem = NULL;
	i = 0;
	mem = (unsigned char *)malloc(size);
	if (mem)
	{
		while (size)
		{
			mem[i] = 0;
			i++;
			size--;
		}
	}
	return ((void *)mem);
}
