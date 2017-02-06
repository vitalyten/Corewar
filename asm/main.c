/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:03:42 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/05 19:26:36 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	showerr()
{
	ft_printf("ERROR\n");
	exit(EXIT_FAILURE);
}

void	envinit(t_en *env)
{
	env->header = (t_header *)malloc(sizeof(t_header));
	if (!env->header)
		showerr();
	env->header->magic = COREWAR_EXEC_MAGIC;
	env->header->prog_size = 0;
	env->file = NULL;
	env->src = NULL;
}

void	checkfile(t_en *env)
{
	int	len;

	len = ft_strlen(env->file);
	if (len < 3)
		showerr();
	if (env->file[len - 1] != 's' || env->file[len - 2] != '.')
		showerr();
}

int		isempty(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

t_src	*srcalloc(char *str, int i)
{
	t_src *src;

	if (!(src = (t_src *)malloc(sizeof(t_src))))
		showerr();
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
		showerr();
	while (get_next_line(fd, &str) > 0)
		if (str[0] != COMMENT_CHAR && !isempty(str))
		{
			if ((tmp = ft_strchr(str, ';')))
				*tmp = '\0';
			storeline(env, str, ++i);
		}
	close(fd);
}

int		main(int ac, char **av)
{
	t_en	env;
	int		i;

	envinit(&env);
	if (ac < 2)
		showerr();
	i = 0;
	while (av[++i])
	{
		env.file = av[i];
		checkfile(&env);
		readfile(&env);
	}
	return (0);
}
