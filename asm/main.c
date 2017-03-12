/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:03:42 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/11 19:15:36 by vtenigin         ###   ########.fr       */
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

// void	printsrc(t_en *env)
// {
// 	t_code	*code;
// 	char	**args;
// 	int		i;

// 	ft_printf("name: %s\n", env->header->prog_name);
// 	ft_printf("size = %d\n", env->header->prog_size);
// 	ft_printf("comment: %s\n", env->header->comment);
// 	code = env->code;
// 	while (code)
// 	{
// 		if (code->label)
// 			ft_printf("i = %d %s\n", code->i, code->label);
// 		if (code->op != -1)
// 		{
// 			i = 0;
// 			ft_printf("i = %d %s", code->i, g_ops[code->op].name);
// 			args = code->args;
// 			while (args[i])
// 				ft_printf(" %s", args[i++]);
// 			ft_printf("\n");
// 		}
// 		code = code->next;
// 	}
// }

int		main(int ac, char **av)
{
	t_en	env;
	// t_src	*tmp;
	// t_code	*code;
	t_label	*label;
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
		writesrc(&env);
	}
	label = env.label;
	// while (label)
	// {
	// 	ft_printf("label = %s\n", label->label);
	// 	label = label->next;
	// }
	// ft_printf("size of short = %d\n", sizeof(short));
	// tmp = env.src;
	// while (tmp)
	// {
	// 	ft_printf("%-4d %s\n", tmp->i, tmp->line);
	// 	tmp = tmp->next;
	// }
	// code = env.code;
	// while (code)
	// {
	// 	if (code->label)
	// 		ft_printf("label = %s\n", code->label);
	// 	code = code->next;
	// }
	freesrc(&env);
	free(env.header);
	return (0);
}
