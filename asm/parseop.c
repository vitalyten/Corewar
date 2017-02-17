/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:23:22 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/16 22:24:56 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*getop(char *str)
{
	char	*tmp;
	char	*op;

	op = NULL;
	if ((tmp = ft_strchr(str, ' ')))
		op = ft_strsub(str, 0, tmp - str);
	else
		showerr("no arguments");
	return (op);
}

char	*getargs(char *str)
{
	while (*str != ' ')
		str++;
	str++;
	return (str);
}
void	parseop(t_en *env, char *str)
{
	char	**args;
	char	*op;
	int		i;

	i = 0;
	trimstr(&str);
	i = ft_strlen(str);
	if (i > 0)
	{
		i = 0;
		op = getop(str);
		args = ft_strsplit(getargs(str), ',');
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
