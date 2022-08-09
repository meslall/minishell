# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/26 14:10:46 by zdasser           #+#    #+#              #
#    Updated: 2022/08/10 00:33:22 by omeslall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/minishell.c lexer/lexer.c lexer/token.c lexer/lexer_utils.c parce/parce.c\
		parce/args.c parce/init_struct.c parce/pipe.c parce/redirections.c\

CC = @gcc -g -lreadline  -fsanitize=address

CFLAGS = -Wall -Wextra -Werror

LFLAGS = -L ~/Desktop/brew/opt/readline/lib

IFLAGS = -I ~/Desktop/brew/opt/readline/include


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