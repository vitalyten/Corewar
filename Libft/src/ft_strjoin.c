/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:17:35 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/12 10:37:24 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_doit(char const *s1, char const *s2, char *dest)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (s1[j] != '\0')
	{
		dest[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;

	if (s1 && s2)
	{
		i = ft_strlen((char *)s1);
		if (!(dest = (char *)
					malloc(sizeof(char) * i + ft_strlen((char *)s2) + 1)))
			return (NULL);
		dest = ft_doit(s1, s2, dest);
		return (dest);
	}
	return ((char *)s1);
}
