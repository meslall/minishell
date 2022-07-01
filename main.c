/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:11:06 by omeslall          #+#    #+#             */
/*   Updated: 2022/07/01 13:57:22 by omeslall         ###   ########.fr       */
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



t_list *ft_filtre(char *line, t_all *all)
{
	t_list *l;
	t_list *temp;
	char **pipe;
	char **sp;
	int i = 0;
	int k = 0;
	

	l = NULL;
	temp = NULL;
	pipe = NULL;
	pipe = ft_split(line,'|');
	while (pipe[i])
	{	
		all = ft_init(all);	
		temp = ft_lstnew(all);
		sp = ft_split(pipe[i], 32);
		k = 0;
		((t_all *)(temp->content))->cmd = sp;
		((t_all *)(temp->content))->ccmd = ft_ccmd(sp);
		ft_lstadd_back(&l,temp);
		i++;
	}
	free(pipe);
	return (l);
}

void    minishell(char *line, t_all *all, char **env, t_var *var)
{
	t_list *filtre;
	(void) env;
	int j;

	j = 0;
	filtre = ft_filtre(line,all);
	check_redirections(filtre);
	check_outfiles(filtre);
	check_heredoc(filtre);
	check_var(filtre);
	j = var_dec(filtre, var);
    if (!j)
		ft_exec(filtre, env);
	// t_list *tmp;
	//  tmp = ((t_all *)(filtre->content))->lenvp;
    //  //while(tmp)
	// //{
	//  	tmp = ft_lstlast(((t_all *)(filtre->content))->lenvp);
	//  	printf("%s\n", (char *)tmp->content);
	//  	//tmp = ((t_all *)(filtre->content))->lenvp->next;
	// // }
}

int main(int ac,char **av,char **envp)
{
	char *line;
	t_all *all;
	t_var *var;

	if (!av || !envp)
		return(0);
	// signal(SIGINT, handle_sigint);
	// signal(SIGQUIT, handle_sigquit);
	all = malloc(sizeof(t_all));
	var = malloc(sizeof(t_var));
	var->name = (char **)ft_calloc(2, sizeof(char *));
	var->name[0] = (char *)ft_calloc(4, sizeof(char));
	var->i = 0;
	all->envp = envp;
	converter(envp, all);
	if (ac == 1)
	{
		while(1)
		{
			line = readline("\033[0;35mminishell:& \033[0;37m");
			if (line && *line)
				add_history (line);
			if(line)
			{
				if(handle_errors(line))
					minishell(line, all, envp, var);
			}
		}
	}
} 