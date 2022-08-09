/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:46:55 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/10 00:32:29 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../src/minishell.h"

void	parse(char *line)
{
	t_token *token;
	t_lexer *lexer;
	t_list	*exec;

	lexer = init_lexer(line);
	token = get_next_token(lexer);
	exec = init_execution();
	while (token)
	{
        // printf("[%s]\n",token->value);
		if(token->type == ARG && ((t_data *)exec->content)->error != 1)
			fill_args(ft_lstlast(exec), token);
		else if(token->type == L_REDIRECTION || token->type == R_REDIRECTION)
			fill_re
		else if(token->type == PIPE)
			fill_pipe(exec);
		free_token(token);
		token = get_next_token(lexer);
	}
	int i;
	i = 0;
	while (exec)
	{	
		i = 0;
		printf("_________________________________________\n\n");
		if(((t_data *)exec->content)->args)
		{
			while(((t_data *)exec->content)->args[i])
			{
				printf("--------------->%s\n",((t_data *)exec->content)->args[i]);
				i++;
			}
		}
		else
			printf("--------------->NULL\n");
		printf("_________________________________________\n");
		exec = exec->next;
	}
	
}