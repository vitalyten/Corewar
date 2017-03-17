/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 21:47:53 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/16 22:41:14 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"



void	showerr(char *msg)
{
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}



void	writechamp(t_en *env)
{
	t_champ			*champ;
	int	i;
	int	j;

	champ = env->champ;
	i = 0;
	while (champ)
	{
		j = -1;
		ft_printf("%s\n", champ->name);
		ft_printf("size = %d\n", champ->size);
		ft_printf("pos = %d\n", i);
		champ->pos = i;
		while (++j < champ->size)
		{
			env->memory[i + j] = champ->code[j];
			env->color[i + j] = champ->color;
		}
		i += MEM_SIZE / env->champnb;
		champ = champ->next;
	}
}

void	printmemory(t_en *env)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("\e[%dm%02x ",env->color[i], env->memory[i]);
		i++;
		if (i % 64 == 0)
			ft_printf("\n");
	}
}





void	envinit(t_en *env)
{
	env->champ = NULL;
	env->champnb = 0;
	ft_bzero(env->memory, MEM_SIZE);
	ft_bzero(env->color, MEM_SIZE);
}

t_proc	*procinit(t_champ *champ)
{
	t_proc	*proc;

	proc = (t_proc *)malloc(sizeof(t_proc));
	// proc->id = champ->id;
	proc->pc = champ->pos;
	proc->color = champ->color;
	proc->carry = 0;
	proc->cycles = 0;
	proc->op = 0;
	proc->acb = 0;
	ft_bzero(proc->args, sizeof(int) * MAX_ARGS_NUMBER);
	ft_bzero(proc->reg, sizeof(int) * REG_NUMBER);
	proc->next = NULL;
	return (proc);
}

void	procreinit(t_proc *proc)
{
	proc->carry = 0;
	proc->cycles = 0;
	proc->op = 0;
	proc->acb = 0;
	ft_bzero(proc->args, sizeof(int) * MAX_ARGS_NUMBER);
	ft_bzero(proc->reg, sizeof(int) * REG_NUMBER);
}

void	makeproc(t_en *env)
{
	t_champ	*champ;
	t_proc	*proc;

	champ = env->champ;
	while (champ)
	{
		proc = procinit(champ);
		proc->next = env->proc;
		env->proc = proc;
		champ = champ->next;
	}
}

int		getdir(t_en *env, t_proc *proc)
{
	int	ar;
	int	i;

	ar = 0;
	i = -1;
	while (++i < 4)
	{
		ar |= env->memory[proc->pc++];
		if(i < 3)
			ar <<= 8;
	}
	return (ar);
}

int		getind(t_en *env, t_proc *proc)
{
	int	ar;
	int	i;

	ar = 0;
	i = -1;
	while (++i < 2)
	{
		ar |= env->memory[proc->pc++];
		if (i == 0)
			ar <<= 8;
		// ft_printf("ar = %x\n", ar);
	}

	return (ar);
}

int		validacb(t_en *env, t_proc *proc)
{
	char	arc[3];
	int		i;

	i = -1;
	arc[0] = (proc->acb & 0xC0) >> 6;
	arc[1] = (proc->acb & 0x30) >> 4;
	arc[2] = (proc->acb & 0xC) >> 2;
	while (++i < g_ops[proc->op - 1].nargs)
	{
		if (arc[i] == IND_CODE)
			arc[i] = T_IND;
		if ((arc[i] & g_ops[proc->op - 1].args[i]) != arc[i])
			return (0);
		if (arc[i] == T_REG)
			proc->args[i] = env->memory[proc->pc++];
		else if (arc[i] == T_DIR && !g_ops[proc->op - 1].index)
			proc->args[i] = getdir(env, proc);
		else
			proc->args[i] = getind(env, proc);

	}
	// ft_printf("\nop = %d \nt_ar0 = %d t_ar1 = %d t_ar2 = %d\n",
		// proc->op, arc[0], arc[1], arc[2]);
	return (1);
}

void	launchproc(t_en *env)
{
	t_proc	*proc;
	// int		*ar;

	proc = env->proc;
	while (proc)
	{
		proc->op = env->memory[proc->pc++];
		if (proc->op > 0 && proc->op < 17)
		{
			if (g_ops[proc->op - 1].acb)
			{
				proc->acb = env->memory[proc->pc++];
				if (validacb(env, proc))
					ft_printf("valid acb\n");
				else
					ft_printf("invalid acb\n");
			}
			else if (g_ops[proc->op - 1].index)
				proc->args[0] = getind(env, proc);
			else
				proc->args[0] = getdir(env, proc);
		}
		ft_printf("arg0 = %d arg1 = %d arg2 = %d\n",
			proc->args[0], proc->args[1], proc->args[2]);
		ft_printf("op == %d acb == %x\n", proc->op, proc->acb);
		proc = proc->next;
	}
}

int		main(int ac, char **av)
{
	t_en	env;
	t_proc *champ;
	int		i;

	envinit(&env);
	if (ac < 2)
		showerr("usage: ./corewar champ1.cor...");
	i = 0;
	while (av[++i])
		readchamp(&env, av[i]);
	writechamp(&env);
	makeproc(&env);
	printmemory(&env);
	launchproc(&env);
	champ = env.proc;
	// while (champ)
	// {
	// 	ft_printf("%d\n", champ->color);
	// 	champ = champ->next;
	// }
}

