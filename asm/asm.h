/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:15:08 by vtenigin          #+#    #+#             */
/*   Updated: 2017/02/26 15:46:19 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

/*
** All sizes are in bytes. It is assumed that an int is 32 bits.
*/

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE


# define REG_CODE				1 // 01
# define DIR_CODE				2 // 10
# define IND_CODE				3 // 11


#define MAX_ARGS_NUMBER			4
#define MAX_PLAYERS				4
#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','

#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

#define REG_NUMBER				16
// NO_CMDS						16 ?

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

typedef char	t_arg_type; // ?

#define T_REG					1 // 0001
#define T_DIR					2 // 0010 || 4 ?
#define T_IND					4 // 0100 || 2 ?
#define T_LAB					8 // 1000 || 2 ?

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		s_code
{
	int				op;
	char			**args;
	char			*label;
	struct s_code	*next;
}					t_code;

typedef struct		s_label
{
	char			*label;
	struct s_label	*next;
}					t_label;

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
	t_label		*label;
	char		*file;
	// int			size;
	int			fd;
}					t_en;

typedef struct		s_op
{
	char	*name;
	int		nargs;
	int		args[MAX_ARGS_NUMBER];
	char	opcode;
	int		ncycles;
	char	*rep;
	int		acb; // arguments coding byte
	int		index; // ?
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
void				writesrc(t_en *env);
void				parsename(t_en *env, char *str);
void				parsecomment(t_en *env, char *str);
// void				parselabel(t_en *env, char *str);
void				parseop(t_en *env, char *str);
char				*getop(char *str);
char				*getargs(char *str);
void				validargs(t_en *env, char **args, int op);
void				checkdir(t_en *env, char *arg, int i, int op);
void				checkind(t_en *env, char *arg, int i, int op);
void				checkreg(t_en *env, char *arg, int i, int op);
int					islabel(char *str, int start, int end);
void				trimstr(char **str); // main
void				addlabel(t_en *env, char *label); // main
void				addcode(t_en *env, int op, char **args); // main
int					spllen(char **spl); // main
char				*trimfree(char *s);
char				*strdupfree(char *src, int start, int end);

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
