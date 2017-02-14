/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:03:42 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/13 21:36:46 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

void	trimstr(char **str)
{
	int len;

	if (str && *str)
	{
		while (ft_iswhitespace(**str))
			(*str)++;
		len = ft_strlen(*str);
		if (len > 0)
		{
			while (ft_iswhitespace((*str)[len - 1]))
				len--;
			(*str)[len] = '\0';
		}
	}
}

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

void	addcode(t_en *env, char *label, char *op)
{
	t_code *tmp;
	t_code *code;

	tmp = (t_code *)malloc(sizeof(t_code));
	tmp->next = NULL;
	tmp->op = NULL;
	tmp->label = NULL;
	if (label)
		tmp->label = ft_strdup(label);
	if (op)
		tmp->op = ft_strdup(op);
	if (env->code)
	{
		code = env->code;
		while (code->next)
			code = code->next;
		code->next = tmp;
	}
	else
		env->code = tmp;
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

void	checkreg(char *arg, int i, int op)
{
	if (!(T_REG & g_ops[op].args[i]))
		showerr("wrong argument");
	if (!*arg)
		showerr("arg syntax error");
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			showerr("arg syntax error");
		arg++;
	}
}

void	checkind(char *arg, int i, int op)
{
	if (!(T_IND & g_ops[op].args[i]))
		showerr("wrong argument");
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			showerr("arg syntax error");
		arg++;
	}
}

void	validargs(char **args, int op)
{
	int i;
	int len;

	i = 0;
	while (args[i])
	{
		trimstr(&args[i]);
		len = ft_strlen(args[i]);
		if ((args[i][len - 1] == SEPARATOR_CHAR && i == g_ops[op].nargs - 1) ||
			(args[i][len - 1] != SEPARATOR_CHAR && i < g_ops[op].nargs - 1))
			showerr("syntax error");
		if (args[i][len - 1] == SEPARATOR_CHAR)
			args[i][len - 1] = '\0';
		if (args[i][0] == 'r')
			checkreg(args[i] + 1, i, op);
		if (ft_isdigit(args[i][0]))
			checkind(args[i], i, op);
		ft_printf("arg#%d   %s\n",i, args[i]);
		i++;
	}
}

void	parseop(t_en *env, char *str)
{
	char	**spl;
	int		len;
	int		i;

	i = 0;
	trimstr(&str);
	spl = ft_strsplit(str, ' ');
	len = spllen(spl);
	if (len > 0)
	{
		while (i < 16)
		{
			if(!ft_strcmp(spl[0], g_ops[i].name))
				break ;
			i++;
		}
		if (i == 16)
			showerr("name syntax error");
		if (g_ops[i].nargs != len - 1)
			showerr("wrong number of arguments");
		validargs(spl + 1, i);
	}
	ft_printf("parseop   %s\n", str);
	env->size++;
}

void	parsesrc(t_en *env)
{
	t_src	*src;
	char	*tmp;

	src = env->src;
	while (src)
	{
		if (ft_strstr(src->line, NAME_CMD_STRING))
			parsename(env, src->line);
		else if (ft_strstr(src->line, COMMENT_CMD_STRING))
			parsecomment(env, src->line);
		else if ((tmp = ft_strchr(src->line, LABEL_CHAR))
			&& !ft_strchr(src->line, DIRECT_CHAR))
		{
			if (tmp - src->line > 0)
			{
				//if (*(tmp - 1) != DIRECT_CHAR)
					parselabel(env, src->line);
			}
		}
		else
			parseop(env, src->line);
		src = src->next;
	}
}

int		main(int ac, char **av)
{
	t_en	env;
	t_src	*tmp;
	t_code	*code;
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
	code = env.code;
	while (code)
	{
		if (code->label)
			ft_printf("label = %s\n", code->label);
		code = code->next;
	}
	freesrc(&env);
	return (0);
}






































