/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 15:31:41 by vtenigin          #+#    #+#             */
/*   Updated: 2016/09/26 17:57:55 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tdst;
	char	*tsrc;
	size_t	i;

	i = 0;
	tdst = (char *)dst;
	tsrc = (char *)src;
	while (i < n)
	{
		tdst[i] = tsrc[i];
		i++;
	}
	return ((void *)dst);
}
