/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:51:19 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/06 16:42:19 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <signal.h>

typedef struct s_token
{
    char *value;
    enum
    {
        ARG,
        REDIRECTION = '>',
        PIPE = '|',
        DOUBLEQOUATE = '"',
        SINGLEQOUATE = '\'',
    } type;
    
}        t_token;

typedef struct t_lexer
{
    char *line;
    size_t len_line;
    char c;
    unsigned int i;
	unsigned int j;
}       t_lexer;

t_lexer	*init_lexer(char *line);
void	lexer_advance(t_lexer *lexer);
t_token	*get_next_token(t_lexer *lexer);
t_token	*init_token(char *value,int type);
t_token *fill_token(t_lexer *lexer);
int		get_type(char *value);
int		is_a_special_char(char c);
void	parse(char *line);
int     ft_strcmp(char *s1, char *s2);
int     ft_strequ(char *s1, char *s2);
void    lexer_skip_whitespaces(t_lexer *lexer);
t_token *arg_token(t_lexer *lexer);

int	handle_errors(char *argv);

#endif    