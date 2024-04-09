# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/24 23:16:33 by luguimar          #+#    #+#              #
#    Updated: 2024/04/09 20:02:17 by luguimar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/main.c src/utils.c

OBJS = ${SRC:.c=.o}

CC = cc -pthread -g
REMOVE = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I ./include
MAKE = make -C

$(NAME): ${OBJS}
		${CC} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean clean all

.PHONY: all clean fclean re
