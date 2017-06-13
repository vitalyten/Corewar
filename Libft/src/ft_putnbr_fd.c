/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkannema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:58:14 by vkannema          #+#    #+#             */
/*   Updated: 2016/11/10 12:38:09 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_max_value_fd(int fd)
{
	char	*str;
	int		i;

	str = "2147483648";
	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n < 0 && n > -2147483648)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_max_value_fd(fd);
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	if (n <= 9 && n >= 0)
	{
		ft_putchar_fd(n + 48, fd);
	}
}
