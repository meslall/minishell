/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:11:06 by omeslall          #+#    #+#             */
/*   Updated: 2022/05/23 20:50:02 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_filtre(char *line, t_all *all)
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
	
	while (l)
	{
		i = 0;
		printf("---------------------------\n");
		while (((t_all *)l->content)->cmd[i])
		{
			printf("%s\n", ((t_all *)l->content)->cmd[i]);
			i++;
		}
		printf("---------------------------\n");
		l = l->next;
	}
	

	return(l);
}

void    minishell(char *line,t_all *all)
{
	t_list *filtre;
	
	filtre = ft_filtre(line,all);
}

int main(int ac,char **av,char **envp)
{
	char *line;
	t_all *all;

	if (!av || !envp)
		return(0);
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
				minishell(line,all);
		}
	}
}