/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/02/13 18:55:21 by vtenigin         ###   ########.fr       */
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
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

/*
live
	The instruction that allows a process to stay alive. It can also record that
	the player whose number is the argument is indeed alive. No argument’s coding
	byte, opcode 1. Oh and its only argument is on 4 bytes.

ld
	Take a random argument and a registry. Load the value of the first argument
	in the registry. Its opcode is 2 and it will change the carry.

st
	take a registry and a registry or an indirect and store the value of the registry
	toward a second argument. Its opcode is 3. For example, st r1, 42 store the
	value of r1 at the address (PC + (42 % IDX_MOD))

add
	Opcode 4. Take three registries, add the first two, and place the result in the
	third, right before modifying the carry.

sub
	Same as add, but with the opcode 5, and uses a substraction.

and
	Apply an & (bit-to-bit AND) over the first two arguments and store the result
	in a registry, which is the third argument. Opcode 6. Modifies the carry.

or
	This operation is an bit-to-bit OR, in the same spirit and principle of and, its
	opcode is 7.

xor
	Acts like and with an exclusive OR. Its opcode in octal is 8.

zjmp
	there’s never been, isn’t and will never be an argument’s coding byte behind
	this operation where the opcode is 9. It will take an index and jump to this address
	if the carry is 1.

ldi
	ldi, code is 10. It will use 2 indexes and 1 registry, adding the first
	two, treating that like an address, reading a value of a registry’s size and putting
	it on the third.

sti
	Opcode 11. Take a registry, and two indexes (potentially registries) add the
	two indexes, and use this result as an address where the value of the first parameter
	will be copied.

fork
	there is no argument’s coding byte, take an index, opcode 12. Create a
	new process that will inherit the different states of its father, except its PC, which
	will be put at (PC + (1st parameter % IDX_MOD)).

lld
	Means long-load, so it’s opcode is 13. It the same as ld, but
	without % IDX_MOD. Modify the carry.

lldi
	Opcode 14. Same as ldi, but does not apply any modulo to the addresses.
	It will however, modify the carry.

lfork
	Opcode 15, means long-fork. Same as a fork without modulo in the address.

aff
	The opcode is 16. There is an argument’s coding byte, which is a
	registry, and its content is interpreted by the character’s ASCII value to display on
	the standard output. The code is modulo 256.
*/















