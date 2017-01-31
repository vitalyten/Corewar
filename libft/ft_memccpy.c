/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 14:29:56 by vtenigin          #+#    #+#             */
/*   Updated: 2016/09/26 17:56:28 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*tdst;
	char	*tsrc;

	tdst = (char *)dst;
	tsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		tdst[i] = tsrc[i];
		if ((char)c == tdst[i])
			return (void *)&tdst[i + 1];
		i++;
	}
	return (NULL);
}
