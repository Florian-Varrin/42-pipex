# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 10:27:38 by fvarrin           #+#    #+#              #
#   Updated: 2022/03/05 13:46:06 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

# DIRS
ROOT_DIR			?= $(shell pwd)
SRC_DIR				= ${ROOT_DIR}/srcs/
HEADER_DIR			= ${ROOT_DIR}/includes/
LIBFT_DIR			= ${ROOT_DIR}/libft/

# COMPILER
SRC					= $(addprefix ${SRC_DIR}, main.c programs.c execute.c pipes.c processes.c utils.c)
OBJ					= $(SRC:.c=.o)
NAME 				= pipex
NORM_BIN			= norminette
NORM_FLAGS			= -RCheckForbiddenSourceHeader -RCheckDefine
RM					= rm -f
CFLAGS				= -Wall -Wextra -Werror -I${HEADER_DIR} -I${LIBFT_DIR}includes -g
CC					= gcc
LIBFT_FLAGS			= -L${LIBFT_DIR} -lft
BUFFER_SIZE			= 1024

.PHONY: 	all clean fclean re

${NAME}:	${OBJ}
			@make -C ${LIBFT_DIR} BUFFER_SIZE=${BUFFER_SIZE} all || true
			${CC} ${CFLAGS} ${OBJ} ${LIBFT_FLAGS} -o ${NAME}

all: 		${NAME}

clean:
			${RM} ${OBJ}
			@make -C ${LIBFT_DIR} clean || true

fclean: 	clean
			@make -C ${LIBFT_DIR} fclean || true
			${RM} ${NAME}

re:		fclean ${NAME}

norm:		fclean
			echo "\n\n"
			${NORM_BIN} ${NORM_FLAGS} ${SRC}
			${NORM_BIN} ${NORM_FLAGS} ${HEADER_DIR}
