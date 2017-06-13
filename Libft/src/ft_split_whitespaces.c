/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 11:52:42 by vkannema          #+#    #+#             */
/*   Updated: 2017/04/20 11:54:18 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_nb_words(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while ((str[i] == '\n' || str[i] == ' ' || str[i] == '\t')
				&& str[i] != '\0')
			i++;
		if (str[i] != '\n' && str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
			count++;
		while (str[i] != '\n' && str[i] != ' ' && str[i] != '\t'
				&& str[i] != '\0')
			i++;
	}
	return (count);
}

int		ft_nb_char(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		i++;
	return (i);
}

char	**ft_split_whitespaces(char *str)
{
	char	**tab;
	int		i;
	int		nb_words;
	int		j;

	nb_words = ft_nb_words(str);
	tab = (char**)malloc(sizeof(char*) * (nb_words + 1));
	tab[nb_words] = 0;
	i = 0;
	while (i < nb_words)
	{
		while ((*str == '\n' || *str == ' ' || *str == '\t') && *str != '\0')
			str++;
		tab[i] = (char*)malloc(sizeof(char) * (ft_nb_char(str) + 1));
		j = 0;
		while (*str != '\n' && *str != ' ' && *str != '\t' && *str != '\0')
		{
			tab[i][j] = *str;
			str++;
			j++;
		}
		tab[i][j] = '\0';
		i++;
	}
	return (tab);
}
