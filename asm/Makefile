# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/05 17:57:52 by vtenigin          #+#    #+#              #
#    Updated: 2017/02/05 20:00:30 by vtenigin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

FILES = main.c readfile.c

OBJECTS = $(FILES:.c=.o)

CFLAG = -Wall -Werror -Wextra -g

ATTACH = -L ../libft/ -lft

all: $(NAME)

$(NAME):
	# make -C libft/
	gcc $(CFLAG) -o $(NAME) $(FILES) $(ATTACH)

clean:
	/bin/rm -f $(OBJECTS)
	# make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	# make -C libft/ fclean

re: fclean all
