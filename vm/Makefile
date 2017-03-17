# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/13 22:35:15 by vtenigin          #+#    #+#              #
#    Updated: 2017/03/16 22:41:36 by vtenigin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

FILES = main.c op.c readchamp.c

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
