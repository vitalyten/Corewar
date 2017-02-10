/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:03:42 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/09 21:42:01 by vtenigin         ###   ########.fr       */
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

int		islabel(char *str, int start, int end)
{
	while (str[start] && start < end)
	{
		if (!ft_strchr(LABEL_CHARS, str[start]))
			return (0);
		start++;
	}
	return (1);
}

void	parsename(t_en *env, char *str)
{
	char	*tmp1;
	char	*tmp2;
	int		start;
	int		finish;

	if (env->header->prog_name[0])
		showerr("name error");
	tmp1 = ft_strstr(str, NAME_CMD_STRING);
	if (!isempty(str, 0, tmp1 - str))
		showerr("syntax error");
	if (!(tmp2 = ft_strchr(str, '\"')))
		showerr("name missing");
	start = ft_strlen(NAME_CMD_STRING) + tmp1 - str;
	finish = tmp2 - str;
	if (!isempty(str, start, finish) || finish - start < 1)
		showerr("syntax error");
	if ((tmp1 = ft_strrchr(str, '\"')) == tmp2)
		showerr("name missing");
	if (tmp1 - tmp2 - 1 > PROG_NAME_LENGTH)
		showerr("name too long");
	if (!islabel(str, finish + 1, tmp1 - str)) // reformat name
		showerr("wrong name format");
	if (!isempty(str, tmp1 - str + 1, ft_strlen(str)))
		showerr("syntax error");
	ft_strncpy(env->header->prog_name, tmp2 + 1, tmp1 - tmp2 - 1);
}

void	parsecomment(t_en *env, char *str)
{
	char	*tmp1;
	char	*tmp2;
	int		start;
	int		finish;

	if (env->header->comment[0])
		showerr("comment error");
	tmp1 = ft_strstr(str, COMMENT_CMD_STRING);
	if (!isempty(str, 0, tmp1 - str))
		showerr("syntax error");
	if (!(tmp2 = ft_strchr(str, '\"')))
		showerr("comment missing");
	start = ft_strlen(COMMENT_CMD_STRING) + tmp1 - str;
	finish = tmp2 - str;
	if (!isempty(str, start, finish) || finish - start < 1)
		showerr("syntax error");
	if ((tmp1 = ft_strrchr(str, '\"')) == tmp2)
		showerr("comment missing");
	if (tmp1 - tmp2 - 1 > COMMENT_LENGTH)
		showerr("comment too long");
	// if (!islabel(str, finish + 1, tmp1 - str)) check comment format
	// 	showerr("wrong name format");
	if (!isempty(str, tmp1 - str + 1, ft_strlen(str)))
		showerr("syntax error");
	ft_strncpy(env->header->comment, tmp2 + 1, tmp1 - tmp2 - 1);
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
		tmp->op = op;
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

void	parselabel(t_en *env, char *str)
{
	char	*tmp;

	while (ft_iswhitespace(*str))
		str++;
	tmp = ft_strchr(str, LABEL_CHAR);
	if (!islabel(str, 0, tmp - str))
		showerr("invalid label");
	if (!isempty(str, tmp - str + 1, ft_strlen(str)))
		showerr("label syntax error");
	*tmp = '\0';
	addcode(env, str, NULL);
}

void	parseop(t_en *env, char *str)
{
	char	**spl;
	int 	len;

	while (ft_iswhitespace(*str))
		str++;
	len = ft_strlen(str);
	while (ft_iswhitespace(str[len - 1]))
		len--;
	str[len] = '\0';
	spl = ft_strsplit(str, ' ');
	// while (spl)
	// {
	// 	ft_printf("%s\n", *spl);
	// 	spl++;
	// }
	ft_printf("parseop %s\n", str);
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






































