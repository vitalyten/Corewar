/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_c_cap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 15:21:11 by vkannema          #+#    #+#             */
/*   Updated: 2017/01/18 19:03:23 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char		*ft_fill_str(char *str, unsigned int nb)
{
	int	i;
	int	end;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == 'x')
		{
			end = nb % 2;
			nb = (nb - end) / 2;
			str[i] = end + '0';
			i--;
		}
		else
			i--;
	}
	return (str);
}

static int		*convert_to_int(int *ret, int tab, int i, char *str)
{
	int	k;
	int	nb;
	int	j;

	nb = 0;
	j = 1;
	k = 1;
	while (tab >= 0)
	{
		while (k <= 8 && i >= 0)
		{
			if (str[i] == '1')
				nb = nb + j;
			j *= 2;
			i--;
			k++;
		}
		ret[tab] = nb;
		k = 1;
		nb = 0;
		tab--;
		j = 1;
	}
	return (ret);
}

int				writechar(char *str, int tab, t_env *env)
{
	int	i;
	int *res;

	i = ft_strlen(str) - 1;
	env->size += tab + 1;
	res = (int *)malloc(sizeof(int) * tab);
	res[0] = 0;
	res[1] = 0;
	res[2] = 0;
	res[3] = 0;
	res = convert_to_int(res, tab, i, str);
	write(1, &res[0], 1);
	write(1, &res[1], 1);
	write(1, &res[2], 1);
	write(1, &res[3], 1);
	ft_memdel((void *)&res);
	return (0);
}

static int		ft_printc(unsigned int nb, t_env *env, int size, char *octes)
{
	int		tab;
	char	*ret;

	if (size <= 7)
	{
		write(1, &nb, 1);
		return (env->size++);
	}
	else if (size <= 11)
		tab = 1;
	else if (size > 11 && size <= 16)
		tab = 2;
	else
		tab = 3;
	ret = ft_fill_str(octes, nb);
	writechar(octes, tab, env);
	ft_memdel((void *)&octes);
	return (0);
}

int				ft_print_c_cap(va_list ap, t_env *env)
{
	unsigned int	nb;
	int				size;
	char			*octes;

	nb = va_arg(ap, unsigned int);
	size = ft_size_bin(nb);
	octes = NULL;
	if (size <= 7)
	{
		write(1, &nb, 1);
		return (env->size++);
	}
	else if (size <= 11 && size > 7)
		octes = ft_strdup("110xxxxx10xxxxxx");
	else if (size > 11 && size <= 16)
		octes = ft_strdup("1110xxxx10xxxxxx10xxxxxx");
	else
		octes = ft_strdup("11110xxx10xxxxxx10xxxxxx10xxxxxx");
	ft_printc(nb, env, size, octes);
	return (0);
}
