/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 13:41:02 by vtenigin          #+#    #+#             */
/*   Updated: 2016/09/30 13:45:30 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	*s1;
	char	*s2;
	char	tmp;

	s1 = str;
	s2 = str + ft_strlen(str) - 1;
	while (s1 < s2)
	{
		tmp = *s1;
		*s1 = *s2;
		*s2 = tmp;
		s1++;
		s2--;
	}
	return (str);
}
