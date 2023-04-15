NAME		= philo
SRCS		= philo.c philo_utils1.c philo_utils2.c utils.c

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pthread -fsanitize=thread -g
RM		= rm -f

all:		${NAME}

${NAME}:	${SRCS}
			$(CC) $(CFLAGS) $^ -o $@

clean:
			$(RM)

fclean:	clean
			$(RM) ${NAME}

re:			fclean all

.PHONY: all clean fclean re
