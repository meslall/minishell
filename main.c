/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:11:06 by omeslall          #+#    #+#             */
/*   Updated: 2022/05/29 13:10:53 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_sigint(int sig)
// {
// 	if (sig != SIGINT)
// 		return ;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	handle_sigquit(int sig)
// {
// 	if (sig != SIGQUIT)
// 		return ;
// 	rl_on_new_line();
// }


t_list *ft_filtre(char *line, t_all *all, char **env)
{
	t_list *l;
	t_list *temp;
	char **pipe;
	char **sp;
	int i = 0;
	

	l = NULL;
	temp = NULL;
	pipe = NULL;
	pipe = ft_split(line,'|');
	while (pipe[i])
	{	
		all = ft_init(all);	
		temp = ft_lstnew(all);
		sp = ft_split(pipe[i],' ');
		((t_all *)temp->content)->cmd = sp;
		ft_lstadd_back(&l,temp);
		i++;
	}
	check_redirections(l);
    ft_exec(l, env);
	return(l);
}

void    minishell(char *line,t_all *all, char **env)
{
	t_list *filtre;
	
	filtre = ft_filtre(line,all, env);
}

int main(int ac,char **av,char **envp)
{
	char *line;
	t_all *all;

	if (!av || !envp)
		return(0);
	// signal(SIGINT, handle_sigint);
	// signal(SIGQUIT, handle_sigquit);
	all = malloc(sizeof(t_all));
	all->envp = envp;
	converter(envp, all);
	if (ac == 1)
	{    
		while(1)
		{
			line = readline("\033[0;35mminishell:& \033[0;37m");
			if(!line)
				exit(0);
			if (line && *line)
				add_history (line);
			if(handle_errors(line))
			{
				minishell(line,all, envp);
			}
		}
	}
} 