# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vtenigin <vtenigin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/10 19:17:22 by vtenigin          #+#    #+#              #
#    Updated: 2016/12/27 22:00:05 by vtenigin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
PATH_SRC = ./

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = 	$(PATH_SRC)ft_strlen.c \
		$(PATH_SRC)ft_strdup.c \
		$(PATH_SRC)ft_strcpy.c\
		$(PATH_SRC)ft_strncpy.c \
		$(PATH_SRC)ft_strcat.c \
		$(PATH_SRC)ft_strncat.c \
		$(PATH_SRC)ft_strlcat.c \
		$(PATH_SRC)ft_strchr.c \
		$(PATH_SRC)ft_strrchr.c\
		$(PATH_SRC)ft_isalpha.c \
		$(PATH_SRC)ft_isdigit.c \
		$(PATH_SRC)ft_isalnum.c\
		$(PATH_SRC)ft_isascii.c \
		$(PATH_SRC)ft_isprint.c \
		$(PATH_SRC)ft_toupper.c \
		$(PATH_SRC)ft_tolower.c \
		$(PATH_SRC)ft_strstr.c \
		$(PATH_SRC)ft_strnstr.c \
		$(PATH_SRC)ft_bzero.c \
		$(PATH_SRC)ft_memcpy.c \
		$(PATH_SRC)ft_memccpy.c\
		$(PATH_SRC)ft_memmove.c \
		$(PATH_SRC)ft_memchr.c \
		$(PATH_SRC)ft_memcmp.c \
		$(PATH_SRC)ft_memset.c \
		$(PATH_SRC)ft_memdel.c \
		$(PATH_SRC)ft_memalloc.c \
		$(PATH_SRC)ft_strcmp.c \
		$(PATH_SRC)ft_strncmp.c \
		$(PATH_SRC)ft_strnew.c \
		$(PATH_SRC)ft_strdel.c \
		$(PATH_SRC)ft_strclr.c \
		$(PATH_SRC)ft_striter.c \
		$(PATH_SRC)ft_striteri.c \
		$(PATH_SRC)ft_strmap.c \
		$(PATH_SRC)ft_strmapi.c \
		$(PATH_SRC)ft_strequ.c \
		$(PATH_SRC)ft_strnequ.c \
		$(PATH_SRC)ft_strsub.c \
		$(PATH_SRC)ft_strjoin.c \
		$(PATH_SRC)ft_strtrim.c \
		$(PATH_SRC)ft_strsplit.c \
		$(PATH_SRC)ft_strrev.c \
		$(PATH_SRC)ft_strtolower.c \
		$(PATH_SRC)ft_strtoupper.c \
		$(PATH_SRC)ft_strrepchr.c \
		$(PATH_SRC)ft_putchar.c \
		$(PATH_SRC)ft_putstr.c \
		$(PATH_SRC)ft_putendl.c \
		$(PATH_SRC)ft_putnbr.c \
		$(PATH_SRC)ft_putchar_fd.c \
		$(PATH_SRC)ft_putstr_fd.c \
		$(PATH_SRC)ft_putendl_fd.c \
		$(PATH_SRC)ft_putnbr_fd.c \
		$(PATH_SRC)ft_iswhitespace.c \
		$(PATH_SRC)ft_itoa.c \
		$(PATH_SRC)ft_itoa_base.c \
		$(PATH_SRC)ft_lstnew.c \
		$(PATH_SRC)ft_lstdelone.c \
		$(PATH_SRC)ft_lstdel.c \
		$(PATH_SRC)ft_lstadd.c \
		$(PATH_SRC)ft_lstiter.c \
		$(PATH_SRC)ft_lstmap.c \
		$(PATH_SRC)ft_atol.c \
		$(PATH_SRC)get_next_line.c \
		$(PATH_SRC)ft_atoi_base.c \
		$(PATH_SRC)ft_atoi.c \
		$(PATH_SRC)ft_strnjoin.c \
		$(PATH_SRC)ft_printf.c \
		$(PATH_SRC)settype.c \
		$(PATH_SRC)setwidth.c \
		$(PATH_SRC)toabase.c \
		$(PATH_SRC)dconv.c \
		$(PATH_SRC)sconv.c \
		$(PATH_SRC)xconv.c \
		$(PATH_SRC)cconv.c \
		$(PATH_SRC)uconv.c \
		$(PATH_SRC)oconv.c \
		$(PATH_SRC)pconv.c \
		$(PATH_SRC)wchar.c

OBJ = $(patsubst %.c,%.o,$(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all re clean flcean