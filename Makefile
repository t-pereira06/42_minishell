# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/02 11:24:16 by tsodre-p          #+#    #+#              #
#    Updated: 2024/10/07 12:29:21 by tsodre-p         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = libft.a

#----------DIRS----------#

SRCDIR = ./src/
LIBFTDIR = ./libft/
HEADERDIR = ./headers/

SRC =	src/main.c \
		src/free.c \
		src/get_env.c \
		src/input_errors.c \
		src/input_handling.c \
		src/input_utils.c \
		src/prompt.c \
		src/signals.c \
		src/splitter.c \
		src/utils.c \

#----------COMMANDS----------#

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
AR = ar rcs
RM = rm -rf

OBJ = ${SRC:.c=.o}

#----------COLORS----------#
GREEN = \033[0;32m
YELLOW = \033[0;33m
CYAN = \033[1;36m

#--------ART & TEXT--------#
MS = " [ Compiled Minishell ] "
LFT = " [ Compiled Libft ] "

#----------RULES----------#
.c.o:
#@$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o ${<:.c=.o}
			@mkdir -p bin/$(dir $<)
			@$(CC) $(CFLAGS) -c -I$(HEADERDIR) $< -o bin/$*.o

all:		$(NAME)
			@echo "$(GREEN)$(MS)"
			@echo "$(CYAN) [ Generated: $(NAME) ] "

$(LIBFT):
			@cd $(LIBFTDIR) && $(MAKE) -s
			@echo "$(YELLOW)$(LFT)"

$(NAME):	$(OBJ) $(LIBFT)
			@$(CC) $(CFLAGS) $(OBJ:%=bin/%) -lreadline $(LIBFTDIR)$(LIBFT) -o $(NAME)

clean:
			@$(RM) $(OBJ:%=bin/%) $(OBJ_CHECKER)
			@rm -r bin/src
			@cd $(LIBFTDIR) && $(MAKE) -s clean

fclean:		clean
			@$(RM) $(NAME) $(BONUS) $(LIBFT)
			@cd $(LIBFTDIR) && $(MAKE) -s fclean

#aclean:		all clean

re:			fclean all
