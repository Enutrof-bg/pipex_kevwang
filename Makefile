# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 12:04:54 by kevwang           #+#    #+#              #
#    Updated: 2025/07/02 12:04:56 by kevwang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = pipex

FILE = main.c

INCLUDE = -Lft_printf -lftprintf

SRC = ${FILE:.c=.o}

all: ${NAME}

${NAME}:${SRC}
	make -C ft_printf
	${CC} ${CFLAGS} -o $@ $^ ${INCLUDE}

%.o:%.c
	${CC} ${CFLAGS} -c $^

clean:
	make clean -C ft_printf
	rm -f infile
	rm -f a.out
	rm -f main.o

fclean:clean
	make fclean -C ft_printf
	rm -f pipex

re:fclean
	make