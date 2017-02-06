/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:03:42 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/05 20:04:39 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	showerr(void)
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

int		main(int ac, char **av)
{
	t_en	env;
	t_src	*tmp;
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
	tmp = env.src;
	while (tmp)
	{
		ft_printf("%-4d %s\n", tmp->i, tmp->line);
		tmp = tmp->next;
	}
	freesrc(&env);
	return (0);
}
