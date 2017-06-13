/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 11:56:06 by vkannema          #+#    #+#             */
/*   Updated: 2017/03/16 10:20:44 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_put_line(char *str)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = 0;
	while (str[i])
	{
		i++;
		len++;
	}
	dest = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	while (str[i] != '\n' && i < len)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char		*ft_delete(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if ((str[i] && !str[i + 1]) || !str[i])
	{
		ft_strdel(&str);
		return (NULL);
	}
	dest = ft_strdup(str + i + 1);
	ft_strdel(&str);
	return (dest);
}

int				get_next_line(const int fd, char **line)
{
	static char		*buf;
	int				ret;
	char			str[BUFF_SIZE + 1];

	if (fd < 0 || BUFF_SIZE < 0 || !line)
		return (-1);
	if (!buf)
		buf = ft_strnew(1);
	while (!(ft_memchr(buf, '\n', ft_strlen(buf))))
	{
		ret = read(fd, str, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		str[ret] = '\0';
		buf = ft_free_join(buf, str, 0);
		if (ret == 0 && *(buf) == '\0')
			return (0);
		if (ret == 0)
			break ;
	}
	*line = ft_put_line(buf);
	buf = ft_delete(buf);
	return (1);
}
