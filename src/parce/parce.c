/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:46:55 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/08 19:46:57 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	printer(t_list *exec)
{
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
					printf("---((t_data *)exec->content)->inf[%d]--->%s\n",i,((t_data *)exec->content)->inf);
				i++;
			}
			printf("-----------------infiles-------------------------\n\n");
				
		}
		i = 0;
		if(((t_data *)exec->content)->outfiles)
		{
			printf("-----------------outfiles-------------------------\n");
			while(((t_data *)exec->content)->outfiles[i])
			{
					printf("---((t_data *)exec->content)->outfiles[%d]--->%s\n",i,((t_data *)exec->content)->outfiles[i]);
				i++;
			}
			printf("-----------------outfiles-------------------------\n");
				
		}
		i = 0;
		if(((t_data *)exec->content)->append)
		{
			printf("-----------------append-------------------------\n");
			while(((t_data *)exec->content)->append[i])
			{
					printf("---((t_data *)exec->content)->append[%d]--->%s\n",i,((t_data *)exec->content)->append[i]);
				i++;
			}
			printf("-----------------append-------------------------\n");
				
		}
		i = 0;
		if(((t_data *)exec->content)->hd)
		{
			printf("-----------------hd-------------------------\n");
			while(((t_data *)exec->content)->hd[i])
			{
					printf("---((t_data *)exec->content)->hd[%d]--->%s\n",i,((t_data *)exec->content)->hd[i]);
				i++;
			}
			printf("-----------------hd-------------------------\n");
				
		}
		printf("========================================================================================\n");
		exec = exec->next;
	}
}

extern int	g_exit_status;

int	parse(char *line, char **envp)
{
	t_token *token;
	t_lexer *lexer;
	t_list	*exec;

	if(!handle_errors(line))
		return(0);
	lexer = init_lexer(line);
	token = get_next_token(lexer);
	exec = init_execution(envp);
	while (token)
	{
		if(token->type == ARG)
			fill_args(ft_lstlast(exec), token);
		else if(token->type == L_REDIRECTION || token->type == R_REDIRECTION)
			fill_redirections(ft_lstlast(exec), &token, lexer);
		else if(token->type == PIPE)
			fill_pipe(exec, envp);
		free_token(token);
		token = get_next_token(lexer);
	}
	printer(exec);//$"HOME"
	free_exec(exec);
	free(lexer);
	system("leaks minishell");//adfasdf$HOME"'$HOME'"adsfasdf>a
	// if (bulitin(exec))
	// 	g_exit_status = execute_bulitings(exec, envp);
	// else
	// 	start_exec(exec, envp);
	// return (g_exit_status);
	return(0);
}