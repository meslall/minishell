/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:46:55 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/11 17:10:00 by omeslall         ###   ########.fr       */
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

		if(token->type == ARG)
			fill_args(ft_lstlast(exec), token);
		else if(token->type == L_REDIRECTION || token->type == R_REDIRECTION)
			fill_redirections(ft_lstlast(exec), &token, lexer);
		else if(token->type == PIPE)
			fill_pipe(exec);
		free_token(token);
		token = get_next_token(lexer);
	}
	int i;
	i = 0;
	while (exec)
	{	
		printf("========================================================================================\n\n");

		if(((t_data *)exec->content)->args)
		{
			i = 0;
			printf("-----------------args-------------------------\n");
			while(((t_data *)exec->content)->args[i])
			{
					printf("----((t_data *)exec->content)->args[%d]----------->%s\n",i,((t_data *)exec->content)->args[i]);
				i++;
			}
			printf("-----------------args-------------------------\n\n");
		}
			i = 0;
		if(((t_data *)exec->content)->infiles)
		{
			printf("-----------------infiles-------------------------\n");
			while(((t_data *)exec->content)->n_infiles > i)
			{
					printf("---((t_data *)exec->content)->infiles[%d]--->%d\n",i,((t_data *)exec->content)->infiles[i]);
				i++;
			}
			printf("-----------------infiles-------------------------\n");
				
		}
		printf("========================================================================================\n");
		exec = exec->next;
	}
	
}