/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:15:08 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/05 19:25:29 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "op.h"
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

typedef struct	s_src
{
	int				i;
	char			*line;
	struct s_src	*next;
}				t_src;

typedef struct	s_en
{
	t_header	*header;
	t_src		*src;
	char		*file;
}				t_en;
#endif

/*
open
read
lseek
write
close
malloc
realloc
free
perror
strerror
exit
*/
