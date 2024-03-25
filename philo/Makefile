# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/24 23:16:33 by luguimar          #+#    #+#              #
#    Updated: 2024/03/24 23:24:47 by luguimar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c philo.c utils.c init.c threads.c monitor.c

OBJS = ${SRC:.c=.o}

CC = cc -g
REMOVE = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I .
MAKE = make -C

$(NAME): ${OBJS}
		${CC} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
		${MAKE} clean
		${RM} ${OBJS}

fclean: clean
		${MAKE} fclean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
