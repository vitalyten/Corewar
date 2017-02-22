/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:15:08 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/22 15:42:19 by vtenigin         ###   ########.fr       */
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
	int			size;
}					t_en;

typedef struct		s_op
{
	char	*name;
	int		nargs;
	int		args[MAX_ARGS_NUMBER];
	int		opcode;
	int		ncycles;
	char	*rep;
	int		acb; // arguments coding byte
	int		is_index; // ?
}					t_op;

extern t_op			g_ops[17];

// t_op    g_ops[17] =
// {
// 	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
// 	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
// 	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
// 	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
// 	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
// 	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
// 		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
// 	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
// 		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
// 	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
// 		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
// 	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
// 	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
// 		"load index", 1, 1},
// 	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
// 		"store index", 1, 1},
// 	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
// 	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
// 	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
// 		"long load index", 1, 1},
// 	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
// 	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
// 	{0, 0, {0}, 0, 0, 0, 0, 0}
// };

void				readfile(t_en *env);
void				storeline(t_en *env, char *str, int i);
t_src				*srcalloc(char *str, int i);
void				checkfile(t_en *env);
int					isempty(char *str, int start, int end);
void				showerr(char *msg); // main
void				envinit(t_en *env);
void				freesrc(t_en *env);
void				parsesrc(t_en *env);
void				parsename(t_en *env, char *str);
void				parsecomment(t_en *env, char *str);
void				parselabel(t_en *env, char *str);
void				parseop(t_en *env, char *str);
char				*getop(char *str);
char				*getargs(char *str);
void				validargs(char **args, int op);
void				checkdir(char *arg, int i, int op);
void				checkind(char *arg, int i, int op);
void				checkreg(char *arg, int i, int op);
int					islabel(char *str, int start, int end);
void				trimstr(char **str); // main
void				addcode(t_en *env, char *label, char *op); // main
int					spllen(char **spl); // main

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
