/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:23:22 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/23 20:20:16 by vtenigin         ###   ########.fr       */
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
	ft_printf("op = %s\n", op);
	return (op);
}

char	*getargs(char *str)
{
	int i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\t')
		i++;
	i++;
	return (ft_strsub(str, i, ft_strlen(str)));
}

void	parseop(t_en *env, char *str)
{
	char	**args;
	char	*op;
	int		i;

	i = 0;
	i = ft_strlen(str);
	if (i > 0)
	{
		i = 0;
		op = getop(str);
		args = ft_strsplit(getargs(str), SEPARATOR_CHAR);
		while (i < 16)
		{
			if(!ft_strcmp(op, g_ops[i].name))
				break ;
			i++;
		}
		if (i == 16)
			showerr("name syntax error");
		validargs(args, i);
		env->size++;
	}
}
