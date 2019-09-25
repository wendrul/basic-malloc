SRCS =	malloc.c\
	main.c\

OBJS = 	${SRCS:.c=.o}

NAME = 	is_my_malloc_working

CC =	gcc

CFLAGS	= -Wall -Werror -Wextra

RM	= rm -f

all:	${NAME}

${NAME}: ${OBJS}
	 ${CC} ${CFLAGS} -o ${NAME} ${OBJS}
	 @echo "\nmamallooooc"
clean:	
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

gud:	fclean all clean

re:	fclean all

.PHONY:	fclean gud all re clean
