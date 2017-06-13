/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:50:20 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/10 12:38:46 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nb_words(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] != c && str[i] != '\0')
			count++;
		while (str[i] != c && str[i] != '\0')
			i++;
	}
	return (count);
}

static int		ft_nb_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

char			**ft_strsplit(char const *str, char c)
{
	char	**tab;
	int		i;
	int		nb_words;

	if (!str)
		return (NULL);
	nb_words = ft_nb_words((char *)str, c);
	if (!(tab = (char**)malloc(sizeof(char*) * (nb_words + 1))))
		return (NULL);
	i = 0;
	while (nb_words--)
	{
		while (*str == c && *str)
			str++;
		tab[i] = ft_strsub((char *)str, 0, ft_nb_char((char *)str, c));
		if (!tab[i])
			return (NULL);
		str = str + ft_nb_char((char *)str, c);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
