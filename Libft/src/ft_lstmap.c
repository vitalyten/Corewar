/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 17:56:12 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/12 10:34:48 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_list;

	new_list = NULL;
	if (lst && f)
	{
		new_list = (*f)(lst);
		if (new_list && lst->next)
			new_list->next = ft_lstmap(lst->next, f);
	}
	return (new_list);
}
