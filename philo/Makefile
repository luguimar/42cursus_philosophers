# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/24 23:16:33 by luguimar          #+#    #+#              #
#    Updated: 2024/04/02 19:33:38 by luguimar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c

OBJS = ${SRC:.c=.o}

CC = cc -pthread -g
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
