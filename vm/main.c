/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 21:47:53 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/13 22:54:57 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	showerr(char *msg)
{
	ft_printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

int		main(int ac, char **av)
{
	if (ac < 2)
		showerr("usage: ./corewar champ1.cor...");
}
