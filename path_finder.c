#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include "minishell.h"

// t_exec *put_envp_in_exec(char **envp)
// {
//     t_exec *exec;
//     int i = 0;
//     exec = malloc(sizeof(t_exec));
//     t_template *temp;
//     while(envp[i])
//     {
//         temp = new_template(envp[i]);
//         lstadd_back(&temp, temp);
//         i++;
//     }
//     while(temp)
//     {
//         printf("%s\n",temp->content);
//         temp =  temp->next;
//     }
//     return (exec);
// }

// void    path_finder(char **envp)
// {
//     char **str;
//     int i = 0;
//     str = envp;


//     while(str[i])
//     {
//         if(ft_strncmp(str[i], "PATH=", 5) == 0)
//             split_path(str[i] + 5, envp,exec);
//         i++;
//     }
// }

// void    fill_struct(char **cmd)
// {
//     t_exec *exec;

//     exec = (malloc(sizeof(t_exec)));
//     exec->cmd = cmd;
// }

// void split_path(char *path, char **envp,t_exec *exec)
// {

//     char **str;
//     char *cmd_test;
//     char;
//     int i = 0;
//     str = ft_split(path, ':');
//     while(str[i])
//     {
//         str[i] = ft_strjoin(str[i], "/");
//         i++;
//     }
//     i = 0;
//     while(exec->cmd[i])
//     {
//         cmd_test = ft_strjoin(cmd_test,cmd[i]);
//         i++; 
//     }
//     i = 0;
//     while(str[i])
//     {
//         if (access_check(str[i], cmd_test, envp))
//             break;
//         i++;
//     }
// }

// int access_check(char *path , char *cmd_test, char **envp)
// {
//     path = ft_strjoin(path, cmd_test);
//     if(access(path, F_OK) == -1)
//     {
//         printf("%s: command not found\n", path);
//     }
//     else
//     {
//         printf("%s\n", path);
//         exec_cmd(path,envp);
//         return(1);
//     }
//     return(0);
// }

// void exec_cmd(char *path, char **envp)
// {
//     pid_t pid;
    
//     char **test;

//     test = (char **)malloc(sizeof(char *) * 2);
//     test [0] = "ls";
//     test [1] = NULL;
//     pid = fork();
//     if (pid == 0)
//     {
//         execve(path , test, envp);
//     }
//     else
//         wait(NULL);
    
// }

// void    exec_cmd(char **cmd, char **envp)
// {
//     pid_t pid;
//     pid = fork();
//     if(pid == 0)
//     {
//         execve(cmd[0], cmd, envp);
//     }
//     else
//     {
//         wait(NULL);
//     }
// }