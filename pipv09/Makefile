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
NAMEBONUS = pipex_bonus

FILE = main.c \
ft_split.c \
ft_strjoin.c \
pipex_utlis.c \
pipex_path.c \
pipex_free.c

FILEBONUS = main_bonus.c \
ft_split.c \
ft_strjoin.c \
pipex_utlis.c \
pipex_path_bonus.c \
pipex_free.c \
pipex_cmd_bonus.c

INCLUDEPRINT = -Lft_printf -lftprintf
INCLUDEGNL = -Lgnl -lgnl

SRC = ${FILE:.c=.o}
SRCBONUS = ${FILEBONUS:.c=.o}

all: ${NAME}

${NAME}:${SRC}
	make -C ft_printf
	${CC} ${CFLAGS} -o ${NAME} $^ ${INCLUDEPRINT}

bonus:${NAMEBONUS}

${NAMEBONUS}:${SRCBONUS}
	make -C ft_printf
	make -C gnl
	${CC} ${CFLAGS} -o ${NAME} $^ ${INCLUDEPRINT} ${INCLUDEGNL}

%.o:%.c
	${CC} ${CFLAGS} -c $^

clean:
	make clean -C ft_printf
	make clean -C gnl
	rm -f main.o \
	main_bonus.o \
	ft_split.o \
	ft_strjoin.o \
	pipex_utlis.o \
	pipex_path.o \
	pipex_path_bonus.o \
	pipex_free.o \
	pipex_cmd_bonus.o \
	outfile

fclean:clean
	rm -f ft_printf/libftprintf.a
	rm -f gnl/libgnl.a
	rm -f pipex

re:fclean
	make