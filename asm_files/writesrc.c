/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writesrc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:06:41 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/13 21:56:36 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	fillblank(int fd, int size)
{
	while (size % 4)
	{
		write(fd, "\0", 1);
		size++;
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

void	writeheader(t_en *env)
{
	void	*tmp;
	size_t	size;

	size = sizeof(env->header->magic);
	tmp = revbytes(&env->header->magic, size);
	write(env->fd, tmp, size);
	fillblank(env->fd, size);
	free(tmp);
	size = sizeof(env->header->prog_name);
	write(env->fd, env->header->prog_name, size);
	fillblank(env->fd, size);
	size = sizeof(env->header->prog_size);
	tmp = revbytes(&env->header->prog_size, size);
	write(env->fd, tmp, size);
	fillblank(env->fd, size);
	free(tmp);
	size = sizeof(env->header->comment);
	write(env->fd, env->header->comment, size);
	fillblank(env->fd, size);
}

char	*getcorname(t_en *env)
{
	char	*ret;
	int		len;

	len = ft_strlen(env->file);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 3))))
		showerr("malloc error");
	ft_strncpy(ret, env->file, len - 1);
	ret[len - 1] = '\0';
	ft_strcat(ret, "cor");
	return (ret);
}

void	writesrc(t_en *env)
{
	char	*file;

	file = getcorname(env);
	if ((env->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		showerr("failed to create file");
	writeheader(env);
	writecode(env);
	close(env->fd);
	ft_strdel(&file);
}
