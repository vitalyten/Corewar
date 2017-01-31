/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 20:31:13 by vtenigin          #+#    #+#             */
/*   Updated: 2016/10/01 15:26:05 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*cur;
	t_list	*tmp;

	ret = NULL;
	while (lst)
	{
		tmp = f(lst);
		tmp->next = NULL;
		if (!ret)
		{
			cur = tmp;
			ret = tmp;
		}
		else
		{
			cur->next = tmp;
			cur = cur->next;
		}
		lst = lst->next;
	}
	return (ret);
}
