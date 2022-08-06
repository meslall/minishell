/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 20:16:02 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/06 16:53:19 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../src/minishell.h"

int		is_a_special_char(char c)
{
    if (c == ' ' || c == '\t' || c == '|' || c == '\0' || c == '>')
        return (1);
    return (0);
}

t_token *fill_token(t_lexer *lexer)
{
    t_token *token = NULL;
    char    *value;
    int     type;
    
    value = ft_substr(lexer->line, lexer->j, lexer->i);
    if (value)
    {
        type = get_type(value);
        token = init_token(value, type);
        lexer->j = lexer->i;
        return (token);
    }
    return(NULL);
}

t_token *arg_token(t_lexer *lexer)
{
    while (!is_a_special_char(lexer->c))
        lexer_advance(lexer);
    return(fill_token(lexer));
}

int get_type(char *value)
{
    if (ft_strequ(value, ">"))
        return (REDIRECTION);
    else if (ft_strequ(value, "|"))
        return (PIPE);
    else if (ft_strequ(value, "\""))
        return (DOUBLEQOUATE);
    else if (ft_strequ(value, "'"))
        return (SINGLEQOUATE);
    return (ARG);
}

void    lexer_skip_whitespaces(t_lexer *lexer)
{
    while (lexer->c == ' ')
        lexer_advance(lexer);
    lexer->j = lexer->i;
}

int ft_strequ(char *s1, char *s2)
{
    if (s1 == NULL || s2 == NULL)
        return (0);
    if (ft_strcmp(s1, s2) == 0)
        return (1);
    return (0);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;
    
    i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0')
        i++;
    return (s1[i] - s2[i]);
}