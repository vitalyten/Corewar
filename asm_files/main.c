/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:03:42 by vtenigin          #+#    #+#             */
/*   Updated: 2017/05/25 21:52:24 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_isnumber(char *num)
{
	if (*num == '-')
		num++;
	while (*num)
	{
		if (*num < '0' || *num > '9')
			return (0);
		num++;
	}
	return (1);
}

void	showerr(char *msg)
{
	ft_printf("error: %s\n", msg);
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
	env->code = NULL;
	env->label = NULL;
	ft_bzero(env->header->prog_name, PROG_NAME_LENGTH);
	ft_bzero(env->header->comment, COMMENT_LENGTH);
}

int		spllen(char **spl)
{
	int i;

	i = 0;
	if (spl && *spl)
		while (spl[i])
			i++;
	return (i);
}

int		main(int ac, char **av)
{
	t_en	env;
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
		storelabel(&env);
		parsesrc(&env);
		validchamp(&env);
		writesrc(&env);
	}
	freesrc(&env);
	free(env.header);
	ft_printf("File.cor created.\n");
	return (0);
}
