/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 14:38:23 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/09 18:20:45 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	print;
	size_t	n;

	i = 0;
	print = 0;
	n = 0;
	if (!s)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (s[n])
	{
		if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n')
		{
			n++;
			print = n;
		}
		else
			n++;
	}
	if (s && print == 0)
		return (ft_strdup(""));
	return (ft_strsub(s, i, (print - i)));
}
