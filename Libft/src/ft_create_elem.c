/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 13:05:11 by vkannema          #+#    #+#             */
/*   Updated: 2017/04/21 14:40:28 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_create_elem(void *data)
{
	t_list *new_elem;

	new_elem = malloc(sizeof(*new_elem));
	new_elem->next = 0;
	new_elem->content = data;
	new_elem->content_size = sizeof(data);
	return (new_elem);
}
