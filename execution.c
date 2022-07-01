/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:29:17 by zdasser           #+#    #+#             */
/*   Updated: 2022/07/01 16:36:39 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	take_quotes(char *s, char c)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while(s[i])
	{
		if(s[i] == c)
		{
			i++;
			while(s[i] !=  c && s[i])
			{
				s[i - 1] = s[i];
				i++;
			}
			s[i - 1] = '\0';
			j = i - 1;
			while(s[i] && s[i] == c)
				i++;
			while(s[i] != c && s[i])
			{
				s[j] = s[i];
				i++;
				j++;
			}
			while(s[j])
			{
				s[j] = '\0';
				j++;
			}
		}
		if(i < (int)ft_strlen(s))
			i++;
	}
}

void	check_quotes(t_list *l)
{
	int i;
	char **s;

	while(l)
	{
		i = 0;
		s = ((t_all *)l->content)->ccmd;
		while(s[i])
		{
			if(ft_cmp(s[i], '"'))
				take_quotes(s[i], '"');
			if (ft_cmp(s[i], 39))
				take_quotes(s[i], 39);
			
			i++;
		}
		l = l->next;
	}
}

void print_error(char **s, t_pipe *p)
{
	if(p->ev == 127 && s[0])
	{
		if(s[1])
			printf("%s %s : command not found\n", s[0], s[1]);
		else
			printf("%s : command not found\n", s[0]);
	}
	else if(p->ev == 126 && s[0])
	{
		if(s[1])
			printf("%s %s : permission denied\n", s[0], s[1]);
		else
			printf("%s : permission denied\n", s[0]);
	}
		
}
char *get_ev(t_pipe *p, t_list *l)
{
	int		i;
	char	**env;
	char *tmp;
    char *cmd;

	env = ((t_all *)l->content)->envp;
	i = 0;
	check_quotes(l);
	
	while (p->splitpaths[i])
	{
		cmd = ((t_all *)l->content)->ccmd[0];
		tmp = ft_strjoin(p->splitpaths[i], "/");
		cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		p->ev = 0;
		if (access(cmd, F_OK) == 0)
		{
			if (access(cmd, X_OK) == 0)
				return (cmd);
			else
			p->ev = 126;
		}
		else
			p->ev = 127;
		i++;
	}
	return(NULL);
}

int	*sttc_var(void)
{
	static int i;

	return (&i);
}

void set_sttc(int i)
{
	int *p;

	p = (sttc_var());
	*p = i;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;
	
	i = 0;
	if(!s1 || !s2)
		return(0);
	if(ft_strlen(s1) != ft_strlen(s2))
		return(0);
	while (s1[i] != '\0' && s2[i] != '\0' && s2[i] == s1[i])
		i++;
	if (i < ft_strlen(s1))
		return (0);
	return (1);
}

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

void ft_exec (t_list *l, char **env)
{
   int fd [2];
   t_pipe p;
   int i = 0;
   int j = 0;
  
   int n = ft_lstsize(l);
   int in = 0;
   int	node = 0;
   int ev = 0;
   int n_inf;
   get_path(env, &p);
   
  if(check_dollar(l))
	return;
  else
  {
	while(l)
	{
		
		n_inf = ((t_all *)l->content)->n_inf;
		pipe(fd);
		i = 0;
		if(fork() == 0)
		{
			if(j < n - 1)
			{
				if(((t_all *)l->content)->hd)
					dup2(((t_all *)l->content)->fd, 0);
				else if(n_inf == 0)
					dup2(in, 0);
				else
					dup2(((t_all *)l->content)->inf[n_inf - 1], 0);
				dup2(fd[1], 1);
				close (fd[1]);
				close (fd[0]);
			}
			else
			{
				if(((t_all *)l->content)->hd)
					dup2(((t_all *)l->content)->fd, 0);
				else if(n_inf == 0)
					dup2(in, 0);
				else
					dup2(((t_all *)l->content)->inf[n_inf - 1], 0);
				dup2(((t_all *)l->content)->outf[0], 1);
				close (fd[1]);
				close (fd[0]);
			}
		 	if(!get_ev(&p, l))
			{
				print_error(((t_all *)l->content)->ccmd, &p);
				exit(p.ev);
			}
			else
				execve(get_ev(&p, l), ((t_all *)l->content)->ccmd, env);
		}
		in = dup(fd[0]);
		close (fd[1]);
		close (fd[0]);
		l = l->next;
		j++;
		node++;
	}
	i = 0;
	while(i < n)
	{
		wait(&ev);
		i++;
	}
	
	if(WIFEXITED(ev))
	{
		set_sttc(WEXITSTATUS(ev));
	}
	// printf("\n");
	}
}