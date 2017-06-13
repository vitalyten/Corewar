/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 22:55:15 by vtenigin          #+#    #+#             */
/*   Updated: 2017/05/30 16:32:57 by vkannema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include <fcntl.h>
# include <curses.h>
# include "libft.h"
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MODA(x)				(x % MEM_SIZE)
# define MODR(x)				(x % IDX_MOD)
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
# define RRR					0b01010100
# define IRR					0b11010100
# define DRR					0b10010100
# define RIR					0b01110100
# define IIR					0b11110100
# define DIR					0b10110100
# define RDR					0b01100100
# define IDR					0b11100100
# define DDR					0b10100100

typedef char					t_arg_type;

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

typedef struct					s_op
{
	char						*name;
	int							nargs;
	int							args[MAX_ARGS_NUMBER];
	char						opcode;
	int							ncycles;
	char						*rep;
	int							acb;
	int							index;
}								t_op;

typedef struct					s_champ
{
	int							id;
	char						*name;
	char						*comment;
	char						*code;
	int							color;
	int							size;
	int							assigned;
	int							pos;
	struct s_champ				*next;
}								t_champ;

typedef struct					s_proc
{
	int							champ_id;
	int							proc_nb;
	int							color;
	int							live;
	int							pc;
	int							carry;
	int							to_wait;
	int							alive;
	int							to_inc;
	int							start;
	int							cycles;
	int							op;
	unsigned char				acb;
	int							args[MAX_ARGS_NUMBER];
	int							reg[REG_NUMBER];
	struct s_proc				*next;
}								t_proc;

typedef struct					s_en
{
	int							dump;
	int							assignement;
	int							is_assignment;
	int							start;
	int							nb_proc;
	int							last_rapported;
	int							id_champ;
	int							nb_check;
	int							champnb;
	int							bonus;
	int							assigned_table[4];
	int							lives;
	int							tot_cycle;
	int							die_cycle;
	int							nb_cycles;
	int							colorproc;
	int							ch;
	unsigned char				memory[MEM_SIZE];
	unsigned char				color[MEM_SIZE];
	unsigned char				color_print[MEM_SIZE];
	t_champ						*champ;
	t_proc						*end;
	t_proc						*proc;
	int							fd;
	char						*winner_name;
}								t_en;

typedef struct					s_sti
{
	char						acb;
	unsigned int				where;
	unsigned int				value;
	int							jump;
}								t_sti;

extern t_op						g_ops[17];

void							showerr(char *msg);
int								readchamp(t_en *env, char *file);
t_champ							*champinit();
void							writechamp(t_en *env);
int								is_assignment(char *s, char *s2, t_en *e);
void							*revbytes(void *mem, size_t size);
void							printmemory(t_en *env);
int								validacb(t_en *env, t_proc *proc);
void							add_proc(t_en *e, t_proc *proc, t_proc *new);
void							move_proc(t_en *e);
void							init_operation(t_en *e, t_proc *proc);
void							get_op(t_en *e, t_proc *proc);
void							operation(t_en *e, t_proc *proc);
void							live(t_en *e, t_proc *proc);
void							ld(t_en *e, t_proc *proc);
void							sti(t_en *e, t_proc *proc);
int								definejump(int acb);
void							st(t_en *e, t_proc *proc);
void							add(t_en *e, t_proc *proc);
void							sub(t_en *e, t_proc *proc);
void							zjmp(t_en *e, t_proc *proc);
void							get_args_axo(t_en *e, t_proc *proc);
void							ft_and(t_en *e, t_proc *proc);
void							ft_or(t_en *e, t_proc *proc);
void							ft_xor(t_en *e, t_proc *proc);
void							ft_fork(t_en *e, t_proc *proc);
void							lfork(t_en *e, t_proc *proc);
void							ft_ldi(t_en *e, t_proc *proc);
void							ft_lldi(t_en *e, t_proc *proc);
void							lld(t_en *e, t_proc *proc);
void							aff(t_en *e, t_proc *proc);
int								get_dump(char *s1, char *s2, t_en *env);
int								get_address(int pc, int arg);
char							*find_name(int id, t_en *e);
int								get_hex_sum(int hex1, int hex2);
int								get_hex_sum1(int hex1, int hex2, int hex3,
								int hex4);
int								fill_reg(int nb);
int								get_bonus(char *s, t_en *e);
void							ft_init_ncurses(void);
void							sti(t_en *e, t_proc *proc);
void							ft_print_dump_init(t_en *e);
void							display_game(t_en *e);
void							envinit(t_en *env);
void							makeproc(t_en *env);
void							writechamp(t_en *env);
void							checkmagic(t_en *env);
void							*revbytes(void *mem, size_t size);
int								is_reg(int a1, int a2, int a3);
#endif
