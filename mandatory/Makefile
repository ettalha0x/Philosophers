# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nettalha <nettalha@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 12:32:12 by nettalha          #+#    #+#              #
#    Updated: 2023/04/12 22:28:46 by nettalha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
SRCS		= philo.c philo_utils1.c philo_utils2.c utils.c

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -pthread
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
