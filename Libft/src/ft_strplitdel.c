/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strplitdel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 17:23:34 by vkannema          #+#    #+#             */
/*   Updated: 2017/04/25 17:23:43 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strsplitdel(char **split)
{
	int i;

	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
}
