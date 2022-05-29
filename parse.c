#include"minishell.h"

 void	executing(t_pipe *p, char **args)
{
	int	i;
	char *tmp;
	char *cmd;

	fprintf(stdout,"this is execution\n");
	i = 0;
	
	while (p->splitpaths[i])
		{
			tmp = ft_strjoin(p->splitpaths[i], "/");
			cmd = ft_strjoin(tmp, args[0]);
			free(tmp);
			if (!access(cmd, X_OK))
				execve(cmd, args, p->env_hold);
			i++;
		}
}

int spawn_proc (int in, int out, char **cmd, t_pipe *p)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }

      if (out != 1)
        {
          dup2 (out, 1);
          close (out);
        }

      executing(p, cmd);
    }

  return pid;
}

void ft_exec (t_list *l, char **env)
{
  int i;
  int in, fd [2];
  int n = ft_lstsize(l);
 t_pipe p;
  get_path(env, &p);
 
  i = 0;  
  pipe (fd);
  while(i < n - 1)
  {
      spawn_proc (in, fd [1], ((t_all *)l->content)->cmd, &p);
      close (fd [1]);
      in = fd [0];
	  i++;
	  l = l->next;
 }
  if (in != 0)
    dup2 (in, 0);
	executing(&p, ((t_all *)l->content)->cmd);
}


// int spawn_proc (int in, int out, char **cmd, char **env)
// {
//   pid_t pid;
//   t_pipe p;
//   get_path(env, &p);
//   if ((pid = fork ()) == 0)
//     {
//       if (in != 0)
//         {
//           dup2 (in, 0);
//           close (in);
//         }

//       if (out != 1)
//         {
//           dup2 (out, 1);
//           close (out);
//         }

//       executing(&p, cmd);
//     }

//   return pid;
// }

// void ft_exec (t_list *l, char **env)
// {
//   int i;
//   int in, fd [2];
//   int n = ft_lstsize(l);
 
 
//   i = 0;  
//   pipe (fd);
//   while(i < n - 1)
//   {
//     in = 0;
//       spawn_proc (in, fd [1], ((t_all *)l->content)->cmd, env);
//       close (fd [1]);
//       in = fd [0];
// 	  i++;
// 	  l = l->next;
//  }
//   if (in != 0)
//     dup2 (in, 0);
// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		if (!ft_strncmp(env[i], "PATH", 4))
// 			break ;
// 		i++;
// 	}
// 	char **s = ft_split(&env[i][5], ':');
// 	if (!s)
// 		exit(write(2, "error\n", 6)); 
//   char *tmp;
// 	char *cmd;
// 	i = 0;
	
// 	while (s[i])
// 		{
// 			tmp = ft_strjoin(s[i], "/");
// 			cmd = ft_strjoin(tmp, ((t_all *)l->content)->cmd[0]);
// 			free(tmp);
// 			if (!access(cmd, X_OK))
// 				execve(cmd, ((t_all *)l->content)->cmd, env);
// 			i++;
// 		}
 
// }


int spawn_proc (int in, int out, char **cmd, t_pipe *p)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }

      if (out != 1)
        {
          dup2 (out, 1);
          close (out);
        }

      executing(p, cmd);
    }

  return pid;
}

void ft_exec (t_list *l, char **env)
{
  int i;
  int in, fd [2];
  int n = ft_lstsize(l);
 t_pipe p;
  get_path(env, &p);
 
  i = 0;  
  pipe (fd);
in = 0;
  while(i < n - 1)
  {
      spawn_proc (in, fd [1], ((t_all *)l->content)->cmd, &p);
      close (fd [1]);
      in = fd [0];
	  i++;
	  l = l->next;
 }
  if (in != 0)
    dup2 (in, 0);

//executing(&p, ((t_all *)l->content)->cmd);
spawn_proc (in, fd[1], ((t_all *)l->content)->cmd, &p);
}