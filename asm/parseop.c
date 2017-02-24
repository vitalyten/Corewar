/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:23:22 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/23 21:40:12 by vtenigin         ###   ########.fr       */
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
		validargs(args, i);
		env->size++;
	}
}

/*
srcdf =    l2:         ; start = 0 end = 15
srcdf = 	sti r1,    %:live, 		%1		;something start = 0 end = 26
srcdf =                  ; start = 0 end = 17
==10959== Invalid read of size 1
==10959==    at 0x100000E30: trimfree (main.c:69)
==10959==    by 0x1000016BF: readfile (readfile.c:82)
==10959==    by 0x1000012FB: main (main.c:207)
==10959==  Address 0x100a8f55f is 1 bytes before a block of size 18 alloc'd
==10959==    at 0x10000FA11: malloc (in /Volumes/Storage/goinfre/vtenigin/homebrew/Cellar/valgrind/3.12.0/lib/valgrind/vgpreload_memcheck-amd64-darwin.so)
==10959==    by 0x100000F7C: strdupfree (main.c:92)
==10959==    by 0x1000016B2: readfile (readfile.c:81)
==10959==    by 0x1000012FB: main (main.c:207)
*/
