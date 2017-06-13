/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 15:36:16 by vkannema          #+#    #+#             */
/*   Updated: 2017/05/17 15:37:26 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	writechamp(t_en *env)
{
	t_champ	*champ;
	int		i;
	int		j;

	champ = env->champ;
	i = 0;
	while (champ)
	{
		j = -1;
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

void	checkmagic(t_en *env)
{
	unsigned int	*m;
	unsigned int	magic;

	read(env->fd, &magic, sizeof(COREWAR_EXEC_MAGIC));
	m = (unsigned int *)revbytes(&magic, sizeof(COREWAR_EXEC_MAGIC));
	if (*m != COREWAR_EXEC_MAGIC)
		showerr("wrong file magic");
	free(m);
}
