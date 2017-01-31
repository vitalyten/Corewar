/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepchr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 18:51:04 by vtenigin          #+#    #+#             */
/*   Updated: 2016/10/01 20:06:04 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrepchr(char *str, char c, char r)
{
	char	*tmp;

	tmp = str;
	while (*str)
	{
		if (*str == c)
			*str = r;
		str++;
	}
	return (tmp);
}
