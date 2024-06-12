# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/24 23:16:33 by luguimar          #+#    #+#              #
#    Updated: 2024/06/12 23:41:22 by luguimar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/main.c src/main_extra.c src/utils.c src/actions.c

OBJS = ${SRC:.c=.o}

CC = cc -pthread -g #-fsanitize=thread
REMOVE = rm -f
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I ./include
MAKE = make -C

.c.o:
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
		${CC} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean clean all

.PHONY: all clean fclean re
