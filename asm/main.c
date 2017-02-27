/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:03:42 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/26 16:46:34 by vtenigin         ###   ########.fr       */
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

void	printsrc(t_en *env)
{
	t_code	*code;
	char	**args;
	int		i;

	ft_printf("name: %s\n", env->header->prog_name);
	ft_printf("size = %d\n", env->header->prog_size);
	ft_printf("comment: %s\n", env->header->comment);
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

void	*revbytes(void *mem, size_t size)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (!(ret = malloc(size)))
		showerr("malloc error");
	i = 0;
	j = size - 1;
	while (i < size)
		ret[i++] = ((char *)mem)[j--];
	return ((void *)ret);
}

void	fillblank(int fd, int size)
{
	while (size % 4)
	{
		write(fd, "\0", 1);
		size++;
	}
}

void	writeacb(t_en *env, char **args)
{
	char	acb;
	int		i;

	i = 0;
	acb = 0;
	while (args[i])
	{
		if (args[i][0] == 'r')
			acb |= REG_CODE;
		if (args[i][0] == '%')
			acb |= DIR_CODE;
		if (args[i][0] == ':' || ft_isdigit(args[i][0]))
			acb |= IND_CODE;
		acb <<= 2;
		i++;
	}
	while (i++ < 3)
		acb <<= 2;
	write(env->fd, &acb, sizeof(acb));
}

void	writedir(t_en *env, int op, char *arg)
{
	int		size;
	int		ar;

	size = (g_ops[op].index) ? IND_SIZE : DIR_SIZE;
	if (arg[0] == ':')
		writedirlabel();
	else
	{
		ar = ft_atoi(arg);
		write(env->fd, &ar, size);
	}
}

void	writeind(t_en *env, char *arg)
{
	int		ar;

	if (arg[0] == ':')
		writeindlabel();
	else
	{
		ar = ft_atoi(arg);
		write(env->fd, &ar, IND_SIZE);
	}
}

void	writeargs(t_en *env, int op, char **args)
{
	int		i;
	char	r;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == 'r')
		{
			r = ((char)ft_atoi(args[i] + 1));
			write(env->fd, &r, sizeof(r));
		}
		if (args[i][0] == '%')
			writedir(env, op, args[i] + 1);
		if (args[i][0] == ':' || ft_isdigit(args[i][0]))
			wirteind(env, args[i]);
		i++;
	}
}

void	writecode(t_en *env)
{
	t_code	*code;

	code = env->code;
	while (code)
	{
		if (code->op != -1)
		{
			write(env->fd, &g_ops[code->op].opcode, sizeof(g_ops[code->op].opcode));
			if (g_ops[code->op].acb)
				writeacb(env, code->args);
			writeargs(env, code->op, code->args);
		}
		code = code->next;
	}
}

void	writeheader(t_en *env)
{
	void	*tmp;
	size_t	size;

	size = sizeof(env->header->magic);
	tmp = revbytes(&env->header->magic, size);
	write(env->fd, tmp, size);
	fillblank(env->fd, size);
	free(tmp);
	size = sizeof(env->header->prog_name);
	write(env->fd, env->header->prog_name, size);
	fillblank(env->fd, size);
	size = sizeof(env->header->prog_size);
	tmp = revbytes(&env->header->prog_size, size);
	write(env->fd, tmp, size);
	fillblank(env->fd, size);
	free(tmp);
	size = sizeof(env->header->comment);
	write(env->fd, env->header->comment, size);
	fillblank(env->fd, size);
}

void	writesrc(t_en *env)
{
	char	*file;

	file = getcorname(env);
	printsrc(env);
	ft_printf("%s\n", file);
	if ((env->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		showerr("failed to create file");
	writeheader(env);
	writecode(env);
	close(env->fd);
}

void	listlabel(t_en *env, char *str)
{
	t_label *tmp;
	t_label *label;

	tmp = (t_label *)malloc(sizeof(t_label));
	tmp->next = NULL;
	tmp->label = ft_strdup(str);
	if (env->label)
	{
		label = env->label;
		while (label->next)
			label = label->next;
		label->next = tmp;
	}
	else
		env->label = tmp;
}

void	storelabel(t_en *env)
{
	t_src	*src;
	char	*tmp;

	src = env->src;
	while (src)
	{
		if ((tmp = ft_strchr(src->line, LABEL_CHAR)) &&
			islabel(src->line, 0, tmp - src->line))
		{
			if (!isempty(src->line, tmp - src->line + 1, ft_strlen(src->line)))
				showerr("label syntax error");
			tmp = ft_strsub(src->line, 0, tmp - src->line);
			listlabel(env, tmp);
			ft_strdel(&tmp);
		}
		src = src->next;
	}
}

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
	while (label)
	{
		ft_printf("label = %s\n", label->label);
		label = label->next;
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






































