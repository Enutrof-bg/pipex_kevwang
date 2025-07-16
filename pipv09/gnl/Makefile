CC = cc

CFLAGS = -Wall -Wextra -Werror

FILE = get_next_line.c get_next_line_utils.c
SRC = ${FILE:.c=.o}

%.o:%.c
	${CC} ${CFLAGS} -c $^

NAME = libgnl.a

all: ${NAME}

${NAME}:${SRC}
	ar -rcs -o $@ $^

# get_next_line.o :
# 	${CC} ${CFLAGS} -c get_next_line.c

# get_next_line_utils.o:
# 	${CC} ${CFLAGS} -c get_next_line_utils.c

clean :
	rm -f get_next_line.o \
	get_next_line_utils.o

fclean : clean
	rm -f libgnl.a

re : fclean
	make










# all : get_next_line.o get_next_line_utils.o
# 	ar -rcs -o libget_next_line.a $^

# get_next_line.o :
# 	cc -Wall -Wextra -Werror -c get_next_line.c

# get_next_line_utils.o :
# 	cc -Wall -Wextra -Werror -c get_next_line_utils.c

# clean :
# 	rm -f *.o

# fclean : clean
# 	rm -f *.a

# re : fclean
# 	make