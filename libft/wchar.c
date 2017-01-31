/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:59:11 by vtenigin          #+#    #+#             */
/*   Updated: 2016/12/26 18:12:33 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			**getunicode(char *bin)
{
	char	**ret;
	char	*uc;
	int		len;

	len = ft_strlen(bin);
	if (len < 8)
		uc = fillutf(ft_strdup("0......."), bin);
	else if (len < 12)
		uc = fillutf(ft_strdup("110..... 10......"), bin);
	else if (len < 17)
		uc = fillutf(ft_strdup("1110.... 10...... 10......"), bin);
	else
		uc = fillutf(ft_strdup("11110... 10...... 10...... 10......"), bin);
	ret = ft_strsplit(uc, ' ');
	ft_strdel(&uc);
	ft_strdel(&bin);
	return (ret);
}

char			*fillutf(char *utf, char *bin)
{
	int		bi;
	int		ui;

	bi = ft_strlen(bin) - 1;
	ui = ft_strlen(utf) - 1;
	while (ui)
	{
		while (utf[ui] != '.' && ui)
			ui--;
		if (bi >= 0)
			utf[ui--] = bin[bi--];
		if (bi < 0 && utf[ui] == '.')
			utf[ui--] = '0';
	}
	return (utf);
}

void			printuc(char **uc)
{
	int				i;
	unsigned char	c;

	i = 0;
	while (uc[i])
	{
		c = atocbin(uc[i]);
		write(1, &c, 1);
		i++;
	}
}

char			*ucstostr(wchar_t *ucs)
{
	char			*str;
	char			*ret;
	int				i;
	int				j;
	char			**uc;

	ret = ft_strnew(0);
	i = 0;
	while (ucs[i])
	{
		str = ft_ulltoa_base(ucs[i], 2);
		uc = getunicode(str);
		j = 0;
		while (uc[j])
			j++;
		str = ft_strnew(j);
		j = -1;
		while (uc[++j])
			str[j] = (char)atocbin(uc[j]);
		ret = sjoinfree(ret, str);
		free2d(uc);
		i++;
	}
	return (ret);
}
