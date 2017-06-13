/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:38:42 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/16 17:58:06 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	ind;

	i = 0;
	if (!*to_find)
		return ((char *)str);
	while (str[i] && len > 0)
	{
		j = 0;
		if (len < (size_t)ft_strlen((char *)to_find))
			return (NULL);
		ind = i;
		while (str[ind] == to_find[j] && to_find[j] && str[ind])
		{
			ind++;
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)str + i);
		i++;
		len--;
	}
	return (NULL);
}
