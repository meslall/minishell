# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 14:10:46 by zdasser           #+#    #+#              #
#    Updated: 2022/07/31 23:06:53 by kdoulyaz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c export.c heredoc_utils.c error_handling.c env_var.c minishell_utils.c execution.c cd.c heredoc.c outfiles.c redirections.c exit_value.c builtin/cd.c builtin/pwd.c \

CC = @gcc -g -lreadline

CFLAGS = -Wall -Wextra -Werror

LFLAGS = -L ~/.brew/opt/readline/lib

IFLAGS = -I ~/.brew/opt/readline/include

LIBFT = libft/libft.a

RM = @rm -f

all:		$(NAME)

$(NAME):
			@cd libft && make && make bonus && cd ..
			@stty -echoctl
			$(CC) $(CFLAGS) $(LIBFT) $(SRC) -lreadline $(LFLAGS) $(IFLAGS) -o $(NAME)
			@echo "\033[0;32m®minishell CREATED 🐲\033[0m"

t:
			@./$(NAME)
clean:
			@cd libft && make clean && cd ..

fclean: 	
			@cd libft && make fclean && cd ..
			$(RM) $(NAME)
			@echo "\033[0;31mminishell DELETED 🗑"

re:			fclean all