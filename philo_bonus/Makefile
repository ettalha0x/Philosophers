NAME		= philo_bonus
SRCS		= philo_bonus.c philo_bonus_utils1.c  philo_bonus_utils2.c bonus_utils.c

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pthread
RM		= rm -f

all:		${NAME}

${NAME}:	${SRCS}
			$(CC) $(CFLAGS) $^ -o $@

clean:
			$(RM) ${OBJS}

fclean:	clean
			$(RM) ${NAME}

re:			fclean all

.PHONY: all clean fclean re
