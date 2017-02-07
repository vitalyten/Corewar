/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 19:59:55 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/06 19:38:33 by vtenigin         ###   ########.fr       */
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
	char	*tmp;

	i = 0;
	if ((fd = open(env->file, O_RDONLY)) == -1)
		showerr("can't open file");
	while (get_next_line(fd, &str) > 0)
		if (str[0] != COMMENT_CHAR && !isempty(str, 0, ft_strlen(str)))
		{
			if ((tmp = ft_strchr(str, ';')))
				*tmp = '\0';
			storeline(env, str, ++i);
		}
	close(fd);
}
