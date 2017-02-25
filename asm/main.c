/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:03:42 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/24 21:24:19 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
typedef struct		s_op
{
	char	*name;
	int		nargs;
	char	args[MAX_ARGS_NUMBER];
	char	opcode;
	int		ncycles;
	char	*rep;
	int		acb;
	int		is_index; // ?
}					t_op;
*/

t_op    g_ops[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

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
	env->header->prog_name[0] = 0;
	env->header->comment[0] = 0;
	env->size = 0;
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

void	printsrc(t_en *env)
{
	t_code	*code;
	char	**args;
	int		i;

	ft_printf("%s\n", env->header->prog_name);
	ft_printf("%s\n", env->header->comment);
	code = env->code;
	while (code)
	{
		if (code->label)
			ft_printf("%s\n", code->label);
		if (code->op != -1)
		{
			i = 0;
			ft_printf("%s", g_ops[code->op].name);
			args = code->args;
			while (args[i])
				ft_printf(" %s", args[i++]);
			ft_printf("\n");
		}
		code = code->next;
	}
}

char	*getcorname(t_en *env)
{
	char	*ret;
	int		len;

	len = ft_strlen(env->file);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 3))))
		showerr("malloc error");
	ft_strncpy(ret, env->file, len - 1);
	ret[len - 1] = '\0';
	ft_strcat(ret, "cor");
	return (ret);
}

void	writesrc(t_en *env)
{
	char	*file;

	file = getcorname(env);
	printsrc(env);
	ft_printf("%s\n", file);
}

int		main(int ac, char **av)
{
	t_en	env;
	// t_src	*tmp;
	// t_code	*code;
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
		writesrc(&env);
	}
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
	return (0);
}






































