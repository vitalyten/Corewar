# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkannema <vkannema@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/21 21:10:13 by vkannema          #+#    #+#              #
#    Updated: 2017/03/15 16:50:48 by vkannema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

H_DIR = includes
C_DIR = src
O_DIR = objects

LINKS = -I$(H_DIR)

C_FILES = $(shell find $(C_DIR) -type f | grep "\.c")

O_FILES = $(C_FILES:$(C_DIR)/%.c=$(O_DIR)/%.o)

FLAGS = -Werror -Wextra -Wall

all: $(NAME)

$(NAME): $(O_FILES)
	@ar rcs $@ $^
	@echo "Libft finished"

$(O_DIR)/%.o: $(C_DIR)/%.c
	@mkdir -p $(O_DIR)
	@gcc $(FLAGS) $(LINKS) -o $@ -c $<

clean:
	@echo "Deleting Objects..."
	@rm -rf $(O_DIR)


fclean: clean
	@echo "Deleting libftprintf.a..."
	@rm -f $(NAME)

re : fclean all
