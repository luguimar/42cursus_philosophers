# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/24 23:16:33 by luguimar          #+#    #+#              #
#    Updated: 2024/04/04 04:28:36 by luguimar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/main.c

OBJS = ${SRC:.c=.o}

CC = cc -pthread -g
REMOVE = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I ./include
MAKE = make -C

$(NAME): ${OBJS}
		${CC} ${OBJS} -o ${NAME}

${OBJS}:
		${CC} ${CFLAGS} ${INCLUDE} -c ${SRC} -o ${OBJS}

all: ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean clean all

.PHONY: all clean fclean re
