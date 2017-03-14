/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writecode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:14:17 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/13 21:57:12 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	writeind(t_en *env, t_code *code, char *arg)
{
	short	ar;
	void	*ind;

	if (arg[0] == ':')
		writelabel(env, code, arg + 1, IND_SIZE);
	else
	{
		ar = (short)ft_atoi(arg);
		ind = revbytes(&ar, sizeof(ar));
		write(env->fd, ind, IND_SIZE);
		free(ind);
	}
}

void	writedir(t_en *env, t_code *code, char *arg)
{
	int				size;
	unsigned int	ar;
	short			ars;
	void			*dir;

	size = (g_ops[code->op].index) ? IND_SIZE : DIR_SIZE;
	if (arg[0] == ':')
		writelabel(env, code, arg + 1, size);
	else
	{
		ar = ft_atoi(arg);
		ars = (short)ar;
		if (size == 4)
			dir = revbytes(&ar, sizeof(ar));
		else
			dir = revbytes(&ars, sizeof(ars));
		write(env->fd, dir, size);
		free(dir);
	}
}

void	writeargs(t_en *env, t_code *code)
{
	int		i;
	char	r;
	char	**args;

	args = code->args;
	i = 0;
	while (args[i])
	{
		if (args[i][0] == 'r')
		{
			r = ((char)ft_atoi(args[i] + 1));
			write(env->fd, &r, sizeof(r));
		}
		if (args[i][0] == '%')
			writedir(env, code, args[i] + 1);
		if (args[i][0] == ':' || ft_isdigit(args[i][0]) || args[i][0] == '-')
			writeind(env, code, args[i]);
		i++;
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
		if (args[i][0] == ':' || ft_isdigit(args[i][0]) || args[i][0] == '-')
			acb |= IND_CODE;
		acb <<= 2;
		i++;
	}
	while (i++ < 3)
		acb <<= 2;
	write(env->fd, &acb, sizeof(acb));
}

void	writecode(t_en *env)
{
	t_code	*code;

	code = env->code;
	while (code)
	{
		if (code->op != -1)
		{
			write(env->fd, &g_ops[code->op].opcode,
				sizeof(g_ops[code->op].opcode));
			if (g_ops[code->op].acb)
				writeacb(env, code->args);
			writeargs(env, code);
		}
		code = code->next;
	}
}
