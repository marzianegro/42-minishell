# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnegro <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 14:56:20 by mnegro            #+#    #+#              #
#    Updated: 2023/09/11 21:06:32 by mnegro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### PHONY TARGET ###
.PHONY: all clean fclean libft re

### SILENT TARGET ###
.SILENT:

### VARIABLES (DEFINITION) ###
NAME = minishell
NAME_ARC = libftminishell.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RLFLAGS = -lreadline
RM = rm -f

#### TARGETS ####
FL_SRCS =	binary.c built_ins.c built_ins2.c builtins_utils.c exec_pipe.c \
			exec_red.c exec_toby.c exec_utils.c exec.c free.c here_doc.c img.c \
			init_shell.c init_utils.c main.c misc_utils.c prs_utils.c prs_utils2.c \
			prs.c red_files.c signals.c spl_red.c spl_toby.c spl_utils.c tkn_utils.c \
			vbl_utils.c vbl_utils2.c
DIRSRCS = src/
SRCS = ${addprefix ${DIRSRCS},${FL_SRCS}}

FL_OBJS = ${FL_SRCS:.c=.o}
DIROBJS = obj/
OBJS = ${addprefix ${DIROBJS},${FL_OBJS}}

INCLUDE = ./minishell.h

DIRARC = arc/
ARC = ${addprefix ${DIRARC},${NAME_ARC}}

### (EXPLICIT) RULES ###
${DIROBJS}%.o: ${DIRSRCS}%.c
	@echo "${YELLOW}Compiling:${WHITE} $< ${DEF_COLOR}"
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: libft ${OBJS}
	cp libft/arc/libft.a ${ARC}
	${CC} ${CFLAGS} ${OBJS} -I {INCLUDE} -o ${NAME} ${ARC} ${RLFLAGS}
	@echo "Rule '${GREEN}all${DEF_COLOR}' for mandatory ${NAME} executed successfully!"

all:	${NAME}

clean:
	${MAKE} -C libft clean
	${RM} ${OBJS}
	@echo "Rule '${GREEN}clean${DEF_COLOR}' for ${NAME} executed successfully!"

fclean:
	${MAKE} -C libft fclean
	${RM} ${OBJS} ${NAME} ${ARC}
	@echo "Rule '${GREEN}fclean${DEF_COLOR}' for ${NAME} executed successfully!"

libft:
	${MAKE} -C libft

test: all
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp  ./minishell

re:	fclean all
	@echo "Rule '${GREEN}re${DEF_COLOR}' for ${NAME} executed successfully!"

### (BRIGHT) COLORS ###

DEF_COLOR = \033[0;39m
BLACK = \033[1;90m
RED = \033[1;91m
GREEN = \033[1;92m
YELLOW = \033[1;93m
BLUE = \033[1;94m
MAGENTA = \033[1;95m
CYAN = \033[1;96m
WHITE = \033[1;97m
