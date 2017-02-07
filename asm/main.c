/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:03:42 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/06 22:05:57 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	showerr(char *msg)
{
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	envinit(t_en *env)
{
	env->header = (t_header *)malloc(sizeof(t_header));
	if (!env->header)
		showerr("malloc error");
	env->header->magic = COREWAR_EXEC_MAGIC;
	env->header->prog_size = 0;
	env->file = NULL;
	env->src = NULL;
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
		ft_strdel(&tmp->line);
		free(tmp);
	}
}

void	parsename(t_en *env, char *str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strstr(str, NAME_CMD_STRING);
	if (!isempty(str, 0, tmp1 - str))
		showerr("syntax error");
	if (!(tmp2 = ft_strchr(str, '\"')))
		showerr("name missing");
	
	if ((tmp1 = ft_strrchr(str, '\"')) == tmp2)
		showerr("name missing");
	ft_printf("%s\ndif %d\n",env->file, tmp1 - str);
}

void	parsesrc(t_en *env)
{
	t_src *src;

	src = env->src;
	while (src)
	{
		if (ft_strstr(src->line, NAME_CMD_STRING))
			parsename(env, src->line);
		src = src->next;
	}
}

int		main(int ac, char **av)
{
	t_en	env;
	t_src	*tmp;
	int		i;

	envinit(&env);
	if (ac < 2)
		showerr("usage: ./asm file1.s ...");
	i = 0;
	while (av[++i])
	{
		env.file = av[i];
		checkfile(&env);
		readfile(&env);
		parsesrc(&env);
	}
	tmp = env.src;
	while (tmp)
	{
		ft_printf("%-4d %s\n", tmp->i, tmp->line);
		tmp = tmp->next;
	}
	freesrc(&env);
	return (0);
}
