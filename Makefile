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

FILE = main.c \
ft_split.c \
ft_strjoin.c \
pipex_utlis.c

INCLUDE = -Lft_printf -lftprintf

# DIRPRINT = ft_printf

# FILEPRINTF = ${DIRPRINT}/ft_printf.o ${DIRPRINT}/ft_putcharstr.o ${DIRPRINT}/ft_puthexa.o \
# ${DIRPRINT}/ft_putnbr.o ${DIRPRINT}/ft_putptr.o ${DIRPRINT}/ft_putunsigned.o

SRC = ${FILE:.c=.o}

all: ${NAME}

${NAME}:${SRC}
	make -C ft_printf
	${CC} ${CFLAGS} -o $@ $^ ${INCLUDE}

%.o:%.c
	${CC} ${CFLAGS} -c $^

clean:
	make clean -C ft_printf
	rm -f a.out \
	outfile \
	in.txt \
	main.o \
	ft_split.o \
	ft_strjoin.o \
	pipex_utlis.o

fclean:clean
	make fclean -C ft_printf
	rm -f pipex

re:fclean
	make