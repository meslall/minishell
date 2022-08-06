#include "../src/minishell.h"

t_lexer *init_lexer(char *line)
{
    t_lexer *lexer;
    
    lexer = ft_calloc(1, sizeof(t_lexer));
    lexer->line = line;
    lexer->len_line = ft_strlen(line);
    lexer->i = 0;
    lexer->j = 0;
    lexer->c = line[lexer->i];
    return(lexer);
}

void lexer_advance(t_lexer *lexer)
{
    if(lexer->i < lexer->len_line && lexer->c != '\0')
    {
        lexer->i++;
        lexer->c = lexer->line[lexer->i];
    }
}

void    check_qouate(t_lexer *lexer,int *qouate,char *temp)
{
    if (lexer->c == '"' || lexer->c == 39)
		{
			if(*qouate == 2)
            {
				*qouate = 0;
                *temp = '\0';
            }
			if(*qouate == 0)
				*temp = lexer->c;
			if(*qouate == 0 || lexer->c == *temp)
				*qouate += 1;
		}
}

t_token *get_next_token(t_lexer *lexer)
{
    int qouate;
    char c;

    qouate = 0;
    while (lexer->c != '\0')
    {
        check_qouate(lexer, &qouate,&c);
        if(qouate == 0)
        {
            lexer_skip_whitespaces(lexer);
            if (is_a_special_char(lexer->c))
            {
                lexer_advance(lexer);
                return(fill_token(lexer));
            }
            else
                return(arg_token(lexer));
            lexer_advance(lexer);
        }
        else if (qouate == 2)
            return(arg_token(lexer));
        else
            lexer_advance(lexer);
    }
    return (NULL);
}