#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <readline/readline.h>
#include "libft/libft.h"

typedef struct s_all
{
    char **cmd;
    char **envp;
    t_list *lenvp;
    int hd;
    char *inf;
    char *outf;
} t_all;


void parse(char s);
int	handle_errors(char *argv);
int handle_characters(char *s, int i);
int	handle_quotes(char *s);
int	ft_cmp(char *s, char c);
int check_qoute(char *str);
void converter(char **envp,t_all *all);
t_all *ft_init(t_all *all);
#endif