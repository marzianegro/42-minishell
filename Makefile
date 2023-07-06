# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnegro <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 14:56:20 by mnegro            #+#    #+#              #
#    Updated: 2023/07/06 15:58:06 by mnegro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### PHONY TARGET ###
.PHONY: all clean fclean libft re

### SILENT TARGET ###
.SILENT:

### VARIABLES (DEFINITION) ###
NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

#### TARGETS ####
MSRCS = main.c

MOBJS = ${MSRCS:.c=.o}
DIROBJS = obj/
OBJS = ${addprefix ${DIROBJS},${MOBJS}}

INCLUDE = ./minishell.h

DIRARC = arc/
ARC = ${addprefix ${DIRARC},${NAME_ARC}}

### (EXPLICIT) RULES ###
${DIROBJS}%.o: %.c
	@echo "${YELLOW}Compiling:${WHITE} $< ${DEF_COLOR}"
	${CC} ${CFLAGS} -c $< -o $@

all:	${NAME}

${NAME}: libft ${OBJS}
	cp libft/libft.a ${ARC}
	${CC} ${CFLAGS} ${OBJS} -I {INCLUDE} -o ${NAME} ${ARC}
	@echo "Rule 'all' for mandatory ${NAME} executed successfully!"

clean:
	${MAKE} -C libft clean
	${RM} ${OBJS}
	@echo "Rule 'clean' for ${NAME} executed successfully!"

fclean: clean
	${MAKE} -C libft fclean
	${RM} ${NAME} ${ARC}
	@echo "Rule 'fclean' for ${NAME} executed successfully!"

libft:
	${MAKE} -C libft

re:	fclean all
	@echo "Rule 're' for ${NAME} executed successfully!"

### (BRIGHT) COLORS ###

DEF_COLOR = \033[0;39m
BLACK = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[1;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
