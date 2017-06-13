/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 22:40:26 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/11 09:49:55 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	int				j;
	int				nb;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	j = 0;
	nb = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[j] && str1[i] != '\0'
			&& str2[j] != '\0' && i < n - 1)
	{
		i++;
		j++;
	}
	if (str1[i] != str2[j])
		nb = str1[i] - str2[j];
	return (nb);
}
