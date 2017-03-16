/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 22:55:15 by vtenigin          #+#    #+#             */
/*   Updated: 2017/03/16 16:41:16 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
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

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

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

typedef struct		s_champ
{
	// int				id;
	char			*name;
	char			*comment;
	char			*code;
	int				color;
	int				size;
	int				alive;
	int				pos;
	struct s_champ	*next;
}					t_champ;

typedef struct		s_proc
{
	// int				id;
	// int				pos;
	int				color;
	int				pc;
	int				carry;
	int				cycles;
	int				op;
	char			acb;
	int				args[MAX_ARGS_NUMBER];
	int				reg[REG_NUMBER];
	struct s_proc	*next;
}					t_proc;

typedef struct		s_en
{
	// t_header	*header;
	// t_src		*src;
	// t_code		*code;
	// t_label		*label;
	int				champnb;
	unsigned char	memory[MEM_SIZE];
	unsigned char	color[MEM_SIZE];
	t_champ			*champ;
	t_proc			*proc;
	int				fd;
}					t_en;


extern t_op			g_ops[17];

void				showerr(char *msg);

#endif
