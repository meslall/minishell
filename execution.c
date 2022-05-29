/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:29:17 by zdasser           #+#    #+#             */
/*   Updated: 2022/05/27 20:32:14 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include<unistd.h>
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}

// void	executing(t_pipe *p, char **args)
// {
// 	int	i;
// 	char *tmp;
// 	char *cmd;

// 	fprintf(stdout,"this is execution\n");
// 	i = 0;
	
// 	while (p->splitpaths[i])
// 		{
// 			tmp = ft_strjoin(p->splitpaths[i], "/");
// 			cmd = ft_strjoin(tmp, args[0]);
// 			free(tmp);
// 			if (!access(cmd, X_OK))
// 				execve(cmd, args, p->env_hold);
// 			i++;
// 		}
// }

// void	forking(int in, int out, char **args, t_pipe *p)
// {
// 	int		child;
	
// 	child = fork();
//  	if (child == 0)
//  	{
//  		if (in != 0)
//  		{
//  			dup2 (in, 0);
// 			close (in);
//  		}
//  		if (out != 1)
//  		{
//  			dup2 (out, 1);
// 			close (out);
//  		}
// 		executing(p, args);
// 	}
// }


// void	exit_statu(t_list *l , int re)
// {
// 	if(!ft_strcmp(((t_all *)l->content)->cmd[0], "$?") && ft_lstsize(l) == 1)
// 	{
// 		printf("command not found %i\n", re);
// 	}
// }

// void	ft_exec(t_list *l, int re, char **env)
// {

// 	t_pipe p;
// 	get_path(env, &p);	
// 	int	i;
// 	int in;
// 	i = 0;
// 	in = 0;
// 	p.env_hold = env;
// 	//exit_statu(l, re);
// 	while(l)
// 	{
// 		pipe(p.fd);
// 		forking(in, p.fd[1], ((t_all *)l->content)->cmd ,&p);
// 		close(p.fd[1]);
// 		in = p.fd[0];
// 		i++;
// 		l = l->next;
// 	}
// 	while(wait(&re) != -1);
// }
void	get_path(char **env, t_pipe *p)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strncmp(env[i], "PATH", 4))
			break ;
		i++;
	}
	if (env[i] == NULL)
		exit (write(2, "error path\n", 6));
	p->splitpaths = ft_split(&env[i][5], ':');
	if (!p->splitpaths)
		exit (write(2, "error\n", 6));
}

 void	executing(t_pipe *p, char **args)
{
	int	i;
	char *tmp;
	char *cmd;

	i = 0;
	  printf("edrgergre\n");
	while (p->splitpaths[i])
		{
			tmp = ft_strjoin(p->splitpaths[i], "/");
			cmd = ft_strjoin(tmp, args[0]);
			free(tmp);
			if (!access(cmd, X_OK))
				if(execve(cmd, args, p->env_hold))
					exit(0);
			i++;
		}
}

// void spawn_proc (int in, int out)
// {
 
//     //   if (in != 0)
//     //     {
          
//     //       close (in);
      	
// }


void ft_exec (t_list *l, char **env)
{
  int fd [2];
  t_pipe p;
   int i = 0;
   int j = 0;
   char *tmp;
  char *cmd;
  int n = ft_lstsize(l);
  int in = 0;
  get_path(env, &p);
	while(l)
	{
		pipe(fd);
		i = 0;
		if(fork() == 0)
		 {
			 if(n == 1)
			 {
				dup2(((t_all *)l->content)->inf[0], 0);
		 	  close (fd[1]);
			  close (fd[0]);
			 }
			else if(j == 0 && n > 1)
			 {
			  dup2(((t_all *)l->content)->inf[0], 0);
			  dup2(fd[1], 1);
		 	  close (fd[1]);
			  close (fd[0]);
			 }
			 
			if(j < n - 1)
			  {dup2(in, 0);
			  dup2(fd[1], 1);
		 	  close (fd[1]);
			  close (fd[0]);}
			else
			{
			  dup2(in, 0);
		 	  close (fd[1]);
			  close (fd[0]);
			}
			  
		 	while (p.splitpaths[i])
		 	{
		 		tmp = ft_strjoin(p.splitpaths[i], "/");
		 		cmd = ft_strjoin(tmp, ((t_all *)l->content)->cmd[0]);
		 		free(tmp);
		 		if (!access(cmd, X_OK))
		 		execve(cmd, ((t_all *)l->content)->cmd, env);
		 		i++;
		 	}
		 }
		in = fd[0];
		close (fd[1]);
		l = l->next;
		j++;
	}
	i = 0;
	while(i < n)
	{
		wait(NULL);
		i++;
	}
}




