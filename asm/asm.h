/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:15:08 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/07 20:59:19 by vtenigin         ###   ########.fr       */
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

typedef struct	s_op
{
	char	*name;
	int		no_args;
	char	args[MAX_ARGS_NUMBER];
	char	opcode;
	int		no_cycles;
	char	*des;
	int		has_acb;
	int		is_index;
}				t_op;

void			readfile(t_en *env);
void			storeline(t_en *env, char *str, int i);
t_src			*srcalloc(char *str, int i);
void			checkfile(t_en *env);
int				isempty(char *str, int start, int end);
void			showerr(char *msg);
void			envinit(t_en *env);
void			freesrc(t_en *env);

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
