/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:15:08 by vtenigin          #+#    #+#             */
/*   Updated: 2017/05/17 18:50:05 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include "libft.h"
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','
# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef char	t_arg_type;

typedef struct		s_code
{
	int				i;
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
	int		acb;
	int		index;
}					t_op;

extern t_op			g_ops[17];

void				readfile(t_en *env);
void				storeline(t_en *env, char *str, int i);
t_src				*srcalloc(char *str, int i);
void				checkfile(t_en *env);
int					isempty(char *str, int start, int end);
void				showerr(char *msg);
void				envinit(t_en *env);
void				freesrc(t_en *env);
void				parsesrc(t_en *env);
void				writesrc(t_en *env);
void				writeheader(t_en *env);
void				*revbytes(void *mem, size_t size);
void				writecode(t_en *env);
void				writeacb(t_en *env, char **args);
void				writeargs(t_en *env, t_code *code);
void				writedir(t_en *env, t_code *code, char *arg);
void				writeind(t_en *env, t_code *code, char *arg);
void				writelabel(t_en *env, t_code *code, char *arg, int size);
int					countbytes(t_code *code, int start, int end);
void				storelabel(t_en *env);
void				listlabel(t_en *env, char *str);
int					ft_isnumber(char *num);
char				*getcorname(t_en *env);
void				parsename(t_en *env, char *str);
void				parsecomment(t_en *env, char *str);
void				parseop(t_en *env, char *str);
char				*getop(char *str);
char				*getargs(char *str);
void				validargs(t_en *env, char **args, int op);
void				checkdir(t_en *env, char *arg, int i, int op);
void				checkind(t_en *env, char *arg, int i, int op);
void				checkreg(t_en *env, char *arg, int i, int op);
int					islabel(char *str, int start, int end);
void				trimstr(char **str);
void				addlabel(t_en *env, char *label);
void				addcode(t_en *env, int op, char **args);
int					spllen(char **spl);
char				*trimfree(char *s);
char				*strdupfree(char *src, int start, int end);
void				validchamp(t_en *env);

#endif
