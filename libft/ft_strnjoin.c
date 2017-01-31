/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 20:25:25 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/15 20:27:16 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t len)
{
	char *ret;

	ret = NULL;
	if (s1 && s2)
	{
		if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + len + 1))))
			return (NULL);
		ft_strcpy(ret, s1);
		ft_strncat(ret, s2, len);
	}
	return (ret);
}
