# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/14 15:23:53 by vkannema          #+#    #+#              #
#    Updated: 2017/05/20 21:10:44 by vkannema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
COREWAR = Corewar
ASM_DIR = asm_files
CORE_DIR = vm
O_ASMDIR = asm_files/objects
O_COREDIR = vm/objects
INCLUDES = -I ./includes -I ./Libft/includes
LIB = -L./Libft/ -lftprintf -lcurses
ASM_FILES = $(shell find $(ASM_DIR) -type f | grep "\.c")
O_ASM = $(ASM_FILES:$(ASM_DIR)/%.c=$(O_ASMDIR)/%.o)
CORE_FILES = vm/readchamp.c \
				vm/main.c \
				vm/list.c \
				vm/start_operation.c \
				vm/op.c \
				vm/hex_operation.c \
				vm/bonus.c \
				vm/init_ncurse.c \
				vm/fork.c \
				vm/aff.c \
				vm/ld.c \
				vm/and.c \
				vm/live.c \
				vm/lld.c \
				vm/ldi.c \
				vm/lldi.c \
				vm/xor.c \
				vm/add.c \
				vm/zjmp.c \
				vm/lfork.c \
				vm/or.c \
				vm/sub.c \
				vm/st.c \
				vm/sti.c \
				vm/axo_tools.c \
				vm/move_proc.c \
				vm/display_game.c \
				vm/tools_operations.c \
				vm/parsing.c \
				vm/parsing_champ.c \
				vm/print_game.c \
				vm/init_operations.c

O_CORE = $(CORE_FILES:$(CORE_DIR)/%.c=$(O_COREDIR)/%.o)
FLAGS = -Wall -Wextra -Werror -g

all : $(ASM) $(COREWAR)

$(ASM): $(O_ASM)
	make -C Libft
	@gcc $(FLAGS) $(LIB) $(O_ASM) -o $(ASM)
	@printf "\033[0;33m ASM FINISHED !\033[0;0m\n"

$(O_ASMDIR)/%.o: $(ASM_DIR)/%.c
	@mkdir -p $(O_ASMDIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $< \
	 && printf "\033[0;0m%-34s\033[1;30m -->>\t\033[0;32m$@\033[0;0m\n" "$<"

$(COREWAR): $(O_CORE)
	@gcc $(FLAGS) $(LIB) $(O_CORE) -o $(COREWAR)
	@printf "\033[0;33m COREWAR FINISHED !\033[0;0m\n"

$(O_COREDIR)/%.o: $(CORE_DIR)/%.c
	@mkdir -p $(O_COREDIR)
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $< \
	&& printf "\033[0;0m%-34s\033[1;30m -->>\t\033[0;32m$@\033[0;0m\n" "$<"

clean :
	@rm -rf $(O_ASMDIR) $(O_COREDIR)
	@make clean -C ./Libft
	@echo "Objects cleaned"

fclean : clean
	@make fclean -C ./Libft
	@rm -f $(ASM) $(COREWAR)
	@echo "Deleted exec"

re : fclean all
