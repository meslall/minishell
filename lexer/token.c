#include"../src/minishell.h"

t_token *init_token(char *value, int type)
{
    t_token *token;
    
    token = ft_calloc(1,sizeof(t_token));
    token->value = value;
    token->type = type;
    return(token);
}