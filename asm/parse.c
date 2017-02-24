/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 20:21:19 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/23 20:36:28 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	// if (!islabel(str, finish + 1, tmp1 - str)) // check comment format
	// 	showerr("wrong name format");
	if (!isempty(str, tmp1 - str + 1, ft_strlen(str)))
		showerr("syntax error");
	ft_strncpy(env->header->comment, tmp2 + 1, tmp1 - tmp2 - 1);
}

void	parselabel(t_en *env, char *str)
{
	char	*tmp;

	tmp = ft_strchr(str, LABEL_CHAR);
	if (!isempty(str, tmp - str + 1, ft_strlen(str)))
		showerr("label syntax error");
	tmp = ft_strsub(str, 0, tmp - str);
	// *tmp = '\0';
	ft_printf("label = %s\n", tmp);
	addcode(env, tmp, NULL);
	ft_strdel(&tmp);
}

void	parsesrc(t_en *env)
{
	t_src	*src;
	char	*tmp;

	src = env->src;
	while (src)
	{
		ft_printf("src = %s\n", src->line);
		if (ft_strstr(src->line, NAME_CMD_STRING))
			parsename(env, src->line);
		else if (ft_strstr(src->line, COMMENT_CMD_STRING))
			parsecomment(env, src->line);
		else if ((tmp = ft_strchr(src->line, LABEL_CHAR))
			&& islabel(src->line, 0, tmp - src->line))
			parselabel(env, src->line);
		else
			parseop(env, src->line);
		src = src->next;
	}
}
