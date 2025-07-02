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

SRC = ${FILE:.c=.o}

all: ${NAME}

${NAME}:${SRC}
	${CC} ${CFLAGS} -o $@ $^

%.o:%.c
	${CC} ${CFLAGS} -c $^

clean:
	rm -f main.o

fclean:clean
	rm -f pipex

re:fclean
	make