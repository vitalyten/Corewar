/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 21:47:53 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/15 22:42:06 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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

void	showerr(char *msg)
{
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	checkmagic(t_en *env)
{
	unsigned int	*m;
	unsigned int	magic;

	read(env->fd, &magic, sizeof(COREWAR_EXEC_MAGIC));
	m = (unsigned int *)revbytes(&magic, sizeof(COREWAR_EXEC_MAGIC));
	if (*m != COREWAR_EXEC_MAGIC)
		showerr("wrong file magic");
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
		ft_printf("i = %d\n", i);
		// champ->pos = i;
		while (++j < champ->size)
		{
			env->memory[i + j] = champ->code[j];
			env->color[i + j] = champ->color;
		}
		ft_printf("i = %d\n", i);
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

t_champ	*champinit()
{
	t_champ *champ;

	champ = (t_champ *)malloc(sizeof(t_champ));
	champ->next = NULL;
	champ->alive = 1;
	champ->color = 31;
	champ->name = (char *)malloc(sizeof(char) * (PROG_NAME_LENGTH + 4));
	champ->comment = (char *)malloc(sizeof(char) * (COMMENT_LENGTH + 4));
	champ->code = (char *)malloc(sizeof(char) * CHAMP_MAX_SIZE);
	return (champ);
}

void	readchamp(t_en *env, char *file)
{
	t_champ			*champ;
	t_champ			*tmp;
	unsigned int	size;
	unsigned int	*s;

	champ = champinit();
	if ((env->fd = open(file, O_RDONLY)) == -1)
		showerr("couldn't open file");
	checkmagic(env);
	read(env->fd, champ->name, PROG_NAME_LENGTH + 4);
	read(env->fd, &size, sizeof(int));
	s = (unsigned int *)revbytes(&size, sizeof(int));
	if ((champ->size = *s) > CHAMP_MAX_SIZE)
		showerr("champion is too big");
	free(s);
	read(env->fd, champ->comment, COMMENT_LENGTH + 4);
	read(env->fd, champ->code, champ->size);
	if (++env->champnb > 4)
		showerr("4 champions max");
	if (!env->champ)
		env->champ = champ;
	else
	{
		champ->color++;
		tmp = env->champ;
		while (tmp->next)
		{
			champ->color++;
			tmp = tmp->next;
		}
		tmp->next = champ;
	}
	// ft_printf("%d\n", champ->size);
	// ft_printf("%s\n", champ->name);
	// ft_printf("%s\n", champ->comment);
	// ft_printf("%c\n", champ->code[1]);

}

void	envinit(t_en *env)
{
	env->champ = NULL;
	env->champnb = 0;
	ft_bzero(env->memory, MEM_SIZE);
	ft_bzero(env->color, MEM_SIZE);
}

int		main(int ac, char **av)
{
	t_en	env;
	t_champ *champ;
	int		i;

	envinit(&env);
	if (ac < 2)
		showerr("usage: ./corewar champ1.cor...");
	i = 0;
	while (av[++i])
		readchamp(&env, av[i]);
	writechamp(&env);
	printmemory(&env);
	champ = env.champ;
	// while (champ)
	// {
	// 	ft_printf("\e[31m%s\n%s\e[0m\n\n", champ->name, champ->comment);
	// 	champ = champ->next;
	// }
}

