# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 12:27:30 by kevwang           #+#    #+#              #
#    Updated: 2025/05/02 12:27:31 by kevwang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC = ft_printf.c ft_putcharstr.c ft_puthexa.c ft_putnbr.c ft_putptr.c ft_putunsigned.c

OBJ = ${SRC:.c=.o}

%.o:%.c
	${CC} ${CFLAGS} -c $^

NAME = libftprintf.a

all : libftprintf.a

libftprintf.a : ${OBJ}
	ar -rcs -o $@ $^

# all: ${NAME}

# ${NAME}:
# 	${CC} ${CFLAGS} -c ft_printf.c
# 	${CC} ${CFLAGS} -c ft_putcharstr.c
# 	${CC} ${CFLAGS} -c ft_puthexa.c
# 	${CC} ${CFLAGS} -c ft_putnbr.c
# 	${CC} ${CFLAGS} -c ft_putptr.c
# 	${CC} ${CFLAGS} -c ft_putunsigned.c
# 	ar -rc -o ${NAME} ft_printf.o ft_putcharstr.o ft_puthexa.o ft_putnbr.o ft_putptr.o ft_putunsigned.o


clean :
	rm -f ft_printf.o ft_putcharstr.o ft_puthexa.o ft_putnbr.o ft_putptr.o ft_putunsigned.o

fclean : clean
	rm -f libftprintf.a

re : fclean
	make
