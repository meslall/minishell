/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 18:49:56 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/06 02:22:07 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	ft_dup(int	fd, int	end)
{
	dup2(fd, end);
	close(fd);
}

void	child_p(t_list *exec, int *p, int copy_fd, char **eenv)
{
	int	fdout;

	fdout = -1;
	open_out(exec, &fdout);
	close(p[0]);
	if (exec->next)
		ft_dup(p[1], 1);
	if (fdout != -1)
		ft_dup(fdout, 1);
	if (copy_fd != -1)
		ft_dup(copy_fd, 0);
	if(((t_data *)exec->content)->infiles)
		ft_dup(((t_data *)exec->content)->infiles[((t_data *)exec->content)->n_infiles - 1], 0);
	if (((t_data *)exec->content)->args && execve(find_path(((t_data *)exec->content)->args[0],\
		eenv),((t_data *)exec->content)->args, eenv) == -1)
		write(2, "hadi makhedamach\n", 18);
}
void	start_exec(t_list *exec, char **eenv)
{
	t_list	*lst;
	pid_t	p[2];
	int		tmpin;
	int		tmpout;
	int		pid;
	int		g;
	int		copy_fd;

	g = 0;
	if (bulitin(exec) && g == 0)
	{
		g_glob.g_exit_status = execute_bulitings(exec);
		g_glob.built = 1;
		return ;
	}
	lst = exec;
	copy_fd = -1;
	tmpin = dup(0);
	tmpout = dup(1);
	while(exec)
	{
		pipe(p);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		pid = fork();
		if (pid == -1)
		{
			write(2, "bash: fork: Resource temporarily unavailable\n", 45);
			break ;
		}
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if(((t_data *)exec->content)->inf)
			{
				write(2, "minishell: ", 11);
				write(2, ((t_data *)exec->content)->inf, ft_strlen(((t_data *)exec->content)->inf));
				write(2, ": No such file or directory\n", 28);
				exit(1);
			}
			child_p(exec, p, copy_fd, eenv);
		}
		close(p[1]);
		if (copy_fd != -1)
			close(copy_fd);
		copy_fd = p[0];
		exec = exec->next;
	}
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
	while(lst)
	{
		wait(NULL);
		lst = lst->next;
	}
	init_signal();
}
