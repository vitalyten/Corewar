/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:26:23 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/16 22:27:31 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

void	checkdir(char *arg, int i, int op)
{
	if (!(T_DIR & g_ops[op].args[i]))
		showerr("wrong argument");
	if (ft_strlen(arg) < 1)
		showerr("arg syntax error");
	if (arg[0] == LABEL_CHAR)
	{
		if (!islabel(arg, 1, ft_strlen(arg)))
			showerr("invalid label");
	}
	else
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

	i = spllen(args);
	if (g_ops[op].nargs != i)
		showerr("wrong number of arguments");
	i = 0;
	while (args[i])
	{
		trimstr(&args[i]);
		if (args[i][0] == 'r')
			checkreg(args[i] + 1, i, op);
		else if (ft_isdigit(args[i][0]))
			checkind(args[i], i, op);
		else if (args[i][0] == DIRECT_CHAR)
			checkdir(args[i] + 1, i, op);
		else
			showerr("syntax error");
		i++;
	}
}
