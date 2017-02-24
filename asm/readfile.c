/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:59:55 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/23 20:21:36 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		isempty(char *str, int start, int end)
{
	while (str[start] && start < end)
	{
		if (str[start] != ' ' && str[start] != '\t')
			return (0);
		start++;
	}
	return (1);
}

void	checkfile(t_en *env)
{
	int	len;

	len = ft_strlen(env->file);
	if (len < 3)
		showerr("wrong filename");
	if (env->file[len - 1] != 's' || env->file[len - 2] != '.')
		showerr("wrong filename");
}

t_src	*srcalloc(char *str, int i)
{
	t_src *src;

	if (!(src = (t_src *)malloc(sizeof(t_src))))
		showerr("malloc error");
	src->i = i;
	src->line = str;
	src->next = NULL;
	return (src);
}

void	storeline(t_en *env, char *str, int i)
{
	t_src	*src;

	if (env->src)
	{
		src = env->src;
		while (src->next)
			src = src->next;
		src->next = srcalloc(str, i);
	}
	else
		env->src = srcalloc(str, i);
}

void	readfile(t_en *env)
{
	int		fd;
	int		i;
	char	*str;
	char	*ln;
	char	*tmp;

	i = 0;
	if ((fd = open(env->file, O_RDONLY)) == -1)
		showerr("can't open file");
	while (get_next_line(fd, &ln) > 0)
	{
		if (ln[0] != COMMENT_CHAR && !isempty(ln, 0, ft_strlen(ln)))
		{
			str = ft_strdup(ln);
			if ((tmp = ft_strchr(str, ';')))
				str = strdupfree(str, 0, tmp - str);
			str = trimfree(str);
			if (ft_strlen(str))
				storeline(env, str, ++i);
		}
		ft_strdel(&ln);
	}
	close(fd);
}
