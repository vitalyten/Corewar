/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 10:43:10 by vkannema          #+#    #+#             */
/*   Updated: 2016/12/13 15:24:17 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_join(char *s1, char *s2, int i)
{
	char	*tmp;

	if (!(tmp = ft_strjoin(s1, s2)))
		return (NULL);
	if (i == 0)
		ft_memdel((void **)&s1);
	if (i == 1)
		ft_memdel((void **)&s2);
	if (i == 2)
	{
		ft_memdel((void **)&s1);
		ft_memdel((void **)&s2);
		return (tmp);
	}
	return (tmp);
}
