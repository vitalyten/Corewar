/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/02/22 15:36:22 by vtenigin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
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
*/


t_op    g_ops[17] =
{
/*
live
Opcode 1. The instruction that allows a process to stay alive.
It can also record that the player whose number is the argument is indeed alive. Its only argument is on 4 bytes.
No argument’s coding byte.*/
{"live",	1, {T_DIR},															1,	10,		"alive",			0,	0},
/*
ld
Opcode 2. Take a random argument and a registry. Load the value of the first argument in the registry.
Modifies the carry.*/
{"ld",		2, {T_DIR | T_IND,			T_REG},									2,	5,		"load",				1,	0},
/*
st
Opcode 3. Take a registry and a registry or an indirect and store the value of the registry toward a second argument.
For example, st r1, 42 store the value of r1 at the address (PC + (42 % IDX_MOD))*/
{"st",		2, {T_REG,					T_IND | T_REG},							3,	5,		"store",			1,	0},
/*
add
Opcode 4. Take three registries, add the first two, and place the result in the third.
Modifies the carry.*/
{"add",		3, {T_REG,					T_REG,					T_REG},			4,	10,		"add",				1,	0},
/*
sub
Opcode 5. Take three registries, subtract the first two, and place the result in the third.
Modifies the carry.*/
{"sub",		3, {T_REG,					T_REG,					T_REG},			5,	10,		"subtract",			1,	0},
/*
and
Opcode 6. Apply bit-to-bit AND over the first two arguments and store the result in the third argument.
Modifies the carry.*/
{"and",		3, {T_REG | T_DIR | T_IND,	T_REG | T_IND | T_DIR,	T_REG},			6,	6,		"r1&r2->r3",		1,	0},
/*
or
Opcode 7. Apply bit-to-bit OR over the first two arguments and store the result in the third argument.
Modifies the carry.*/
{"or",		3, {T_REG | T_IND | T_DIR,	T_REG | T_IND | T_DIR,	T_REG},			7,	6,		"r1|r2->r3",		1,	0},
/*
xor
Opcode 8. Apply bit-to-bit XOR over the first two arguments and store the result in the third argument.
Modifies the carry.*/
{"xor",		3, {T_REG | T_IND | T_DIR,	T_REG | T_IND | T_DIR,	T_REG},			8,	6,		"r1^r2->r3",		1,	0},
/*
zjmp
Opcode 9. It will take an index and jump to this address if the carry is 1.
No argument’s coding byte.*/
{"zjmp",	1, {T_DIR},															9,	20,		"jump if zero",		0,	1},
/*
ldi
Opcode 10. It will use 2 indexes and 1 registry, adding the first two, treating that like an address,
reading a value of a registry’s size and putting it on the third.*/
{"ldi",		3, {T_REG | T_DIR | T_IND,	T_DIR | T_REG,			T_REG}, 		10,	25,		"load index",		1,	1},
/*
sti
Opcode 11. Take a registry, and two indexes (potentially registries) add the two indexes,
and use this result as an address where the value of the first parameter will be copied.*/
{"sti",		3, {T_REG,					T_REG | T_DIR | T_IND,	T_DIR | T_REG},	11,	25,		"store index",		1,	1},
/*
fork
Opcode 12. Take an index. Create a new process that will inherit the different states
of its father, except its PC, which will be put at (PC + (1st parameter % IDX_MOD)).
No argument’s coding byte.*/
{"fork",	1, {T_DIR},															12,	800,	"fork",				0,	1},
/*
lld
Opcode 13. Long-load,  It the same as ld, but without % IDX_MOD.
Modifies the carry.*/
{"lld",		2, {T_DIR | T_IND,			T_REG},									13,	10,		"long load",		1,	0},
/*
lldi
Opcode 14. Same as ldi, but does not apply any modulo to the addresses.
Modifies the carry.*/
{"lldi",	3, {T_REG | T_DIR | T_IND,	T_DIR | T_REG,			T_REG},			14,	50,		"long load index",	1,	1},
/*
lfork
Opcode 15. Long-fork. Take an index. Create a new process that will inherit
the different states of its father, except its PC, which will be put at (PC + 1st parameter).
No argument’s coding byte.
Modifies the carry.*/
{"lfork",	1, {T_DIR},															15,	1000,	"long fork",		0,	1},
/*
aff
Opcode 16. There is an argument’s coding byte, which is a registry, and its content is interpreted
by the character’s ASCII value to display on the standard output.*/
{"aff",		1, {T_REG},															16,	2,		"aff",				1,	0},
{0, 		0, {0},																0,	0,		0,					0,	0}
};














