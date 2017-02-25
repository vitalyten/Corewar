/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:23:22 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/24 20:35:22 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*getop(char *str)
{
	char	*tmp;
	char	*op;

	op = NULL;
	if (!(tmp = ft_strchr(str, ' ')))
		tmp = ft_strchr(str, '\t');
	if (!tmp)
		showerr("no arguments");
	op = ft_strsub(str, 0, tmp - str);
	op = trimfree(op);
	return (op);
}

char	*getargs(char *str)
{
	int i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\t')
		i++;
	i++;
	return (ft_strsub(str, i, ft_strlen(str) - i));
}

void	parseop(t_en *env, char *str)
{
	char	**args;
	char	*op;
	char	*tmp;
	int		i;

	i = 0;
	i = ft_strlen(str);
	if (i > 0)
	{
		i = 0;
		op = getop(str);
		tmp = getargs(str);
		args = ft_strsplit(tmp, SEPARATOR_CHAR);
		ft_strdel(&tmp);
		while (i < 16)
		{
			if(!ft_strcmp(op, g_ops[i].name))
				break ;
			i++;
		}
		if (i == 16)
			showerr("name syntax error");
		validargs(env, args, i);
		env->size++;
	}
}
