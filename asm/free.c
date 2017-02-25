/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 20:24:24 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/24 20:34:30 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*trimfree(char *s)
{
	int		start;
	int		end;
	char	*ret;

	ret = NULL;
	if (s)
	{
		start = 0;
		end = ft_strlen(s);
		while (ft_iswhitespace(s[start]))
			start++;
		while (--end >= 0)
			if (!ft_iswhitespace(s[end]))
				break ;
		if (end < start)
		{
			ft_strdel(&s);
			return (ft_strnew(0));
		}
		if (!(ret = ft_strnew(end - start + 1)))
			showerr("malloc error tf");
		ret = ft_strncpy(ret, s + start, end - start + 1);
		ft_strdel(&s);
	}
	return (ret);
}

char	*strdupfree(char *src, int start, int end)
{
	char	*ret;
	int		i;

	if (!src)
		return (NULL);
	if (!(ret = (char *)malloc(sizeof(char) * (end - start + 1))))
		showerr("malloc error df");
	i = 0;
	while (start < end)
		ret[i++] = src[start++];
	ret[i] = '\0';
	ft_strdel(&src);
	return (ret);
}

void	freesrc(t_en *env)
{
	t_src *src;
	t_src *tmp;

	src = env->src;
	while (src)
	{
		tmp = src;
		src = src->next;
		ft_strdel(&(tmp->line));
		free(tmp);
	}
}
