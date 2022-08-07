/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 16:50:37 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/07 21:46:02 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	parse(char *line)
{
	t_token *token;
	t_lexer *lexer;


	lexer = init_lexer(line);
	token = get_next_token(lexer);
	while (token)
	{
		
		token = get_next_token(lexer);
	}
}
int main(int ac,char **av,char **envp)
{
	char *line;

	if (!av || !envp)
		return(0);
	if (ac == 1)
	{
		while(1)
		{
			line = readline("minishell:");
			if (!line)
				break;
			if (line && *line)
				add_history (line);
			if(line)
			{
				
				parse(line);
			}
		}
	}
} 