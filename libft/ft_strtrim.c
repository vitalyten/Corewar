/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 09:48:25 by vtenigin          #+#    #+#             */
/*   Updated: 2016/10/04 22:04:52 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	char	*ret;

	ret = NULL;
	if (s)
	{
		start = 0;
		end = ft_strlen(s);
		while (ft_iswhitespace(s[start]))
			start++;
		while (ft_iswhitespace(s[end - 1]))
			end--;
		if (end < start)
			end = start;
		if (!(ret = ft_strnew(end - start)))
			return (NULL);
		ret = ft_strncpy(ret, s + start, end - start);
	}
	return (ret);
}
