/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:15:08 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/07 21:47:15 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "op.h"
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

typedef struct		s_code
{
	char			*op;
	char			*label;
	struct s_code	*next;
}					t_code;

typedef struct		s_src
{
	int				i;
	char			*line;
	struct s_src	*next;
}					t_src;

typedef struct		s_header
{
  unsigned int	magic;
  char			prog_name[PROG_NAME_LENGTH + 1];
  unsigned int	prog_size;
  char			comment[COMMENT_LENGTH + 1];
}					t_header;


typedef struct		s_en
{
	t_header	*header;
	t_src		*src;
	t_code		*code;
	char		*file;
}					t_en;

typedef struct		s_op
{
	char	*name;
	int		nargs;
	char	args[MAX_ARGS_NUMBER];
	char	opcode;
	int		ncycles;
	char	*rep;
	int		has_acb; // ?
	int		is_index; // ?
}					t_op;

void				readfile(t_en *env);
void				storeline(t_en *env, char *str, int i);
t_src				*srcalloc(char *str, int i);
void				checkfile(t_en *env);
int					isempty(char *str, int start, int end);
void				showerr(char *msg);
void				envinit(t_en *env);
void				freesrc(t_en *env);

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
