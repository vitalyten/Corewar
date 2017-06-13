/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storelabel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:22:44 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/13 22:12:55 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	listlabel(t_en *env, char *str)
{
	t_label *tmp;
	t_label *label;

	tmp = (t_label *)malloc(sizeof(t_label));
	tmp->next = NULL;
	tmp->label = ft_strdup(str);
	if (env->label)
	{
		label = env->label;
		while (label->next)
		{
			if (!ft_strcmp(label->label, str))
				showerr("duplicate label");
			label = label->next;
		}
		if (!ft_strcmp(label->label, str))
			showerr("duplicate label");
		label->next = tmp;
	}
	else
		env->label = tmp;
}

void	storelabel(t_en *env)
{
	t_src	*src;
	char	*tmp;

	src = env->src;
	while (src)
	{
		if ((tmp = ft_strchr(src->line, LABEL_CHAR)) &&
			islabel(src->line, 0, tmp - src->line))
		{
			if (!isempty(src->line, tmp - src->line + 1, ft_strlen(src->line)))
				showerr("label syntax error storelabel");
			tmp = ft_strsub(src->line, 0, tmp - src->line);
			listlabel(env, tmp);
			ft_strdel(&tmp);
		}
		src = src->next;
	}
}
