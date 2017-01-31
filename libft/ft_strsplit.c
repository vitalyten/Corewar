/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/29 19:53:44 by vtenigin          #+#    #+#             */
/*   Updated: 2016/10/04 22:19:15 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*skipchar(const char *str, char c)
{
	while (*str && *str == c)
		str++;
	return (*str == '\0' ? NULL : str);
}

static const char	*skipword(const char *str, char c)
{
	while (*str && *str != c)
		str++;
	return (str);
}

static int			ft_nwords(char const *str, char c)
{
	int	i;

	i = 0;
	while ((str = skipchar(str, c)))
	{
		i++;
		str = skipword(str, c);
	}
	return (i);
}

char				**ft_strsplit(char const *s, char c)
{
	char		**ret;
	char const	*tmp;
	int			nwords;

	ret = NULL;
	if (s)
	{
		nwords = ft_nwords(s, c);
		if (!(ret = (char **)malloc(sizeof(char *) * (nwords + 1))))
			return (NULL);
		ret[nwords] = NULL;
		nwords = 0;
		while ((s = skipchar(s, c)))
		{
			tmp = s;
			s = skipword(s, c);
			ret[nwords++] = ft_strsub(tmp, 0, s - tmp);
		}
	}
	return (ret);
}
