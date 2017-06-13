/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 11:59:16 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/30 12:00:32 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **begin_list)
{
	t_list	*tmp_current;
	t_list	*tmp_prev;
	t_list	*tmp_next;

	tmp_prev = NULL;
	tmp_current = *begin_list;
	while (tmp_current)
	{
		tmp_next = tmp_current->next;
		tmp_current->next = tmp_prev;
		tmp_prev = tmp_current;
		tmp_current = tmp_next;
	}
	*begin_list = tmp_prev;
}
