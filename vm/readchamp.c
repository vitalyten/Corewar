/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readchamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 22:38:58 by vtenigin          #+#    #+#             */
/*   Updated: 2017/05/30 15:21:46 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fill_id(t_champ *champ, t_en *env)
{
	int	i;

	i = 0;
	while (i < 4 && env->assigned_table[i] != 0)
		i++;
	if (i < 4)
	{
		env->assigned_table[i] = 1;
		champ->id = -(i + 1);
	}
}

t_champ	*champinit(t_en *env)
{
	t_champ *champ;

	champ = (t_champ *)malloc(sizeof(t_champ));
	champ->assigned = 0;
	if (env->assignement)
	{
		champ->id = env->assignement;
		champ->assigned = 1;
	}
	else
		fill_id(champ, env);
	champ->next = NULL;
	champ->color = 31;
	champ->name = (char *)malloc(sizeof(char) * (PROG_NAME_LENGTH + 4));
	champ->comment = (char *)malloc(sizeof(char) * (COMMENT_LENGTH + 4));
	champ->code = (char *)malloc(sizeof(char) * CHAMP_MAX_SIZE);
	return (champ);
}

void	readchamp2(t_en *env, t_champ *champ)
{
	t_champ			*tmp;

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
}

int		readchamp(t_en *env, char *file)
{
	t_champ			*champ;
	unsigned int	size;
	unsigned int	*s;

	champ = champinit(env);
	if ((env->fd = open(file, O_RDONLY)) == -1)
		showerr("couldn't open file");
	checkmagic(env);
	read(env->fd, champ->name, PROG_NAME_LENGTH + 4);
	read(env->fd, &size, sizeof(int));
	s = (unsigned int *)revbytes(&size, sizeof(int));
	if ((champ->size = *s) > CHAMP_MAX_SIZE)
		showerr("champion is too big");
	free(s);
	readchamp2(env, champ);
	return (1);
}
