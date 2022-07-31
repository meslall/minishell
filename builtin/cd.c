/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:26:54 by omeslall          #+#    #+#             */
/*   Updated: 2022/07/31 15:33:24 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	is_builtin(char *cmd)
{
	if(!(ft_strncmp(cmd,"cd",2)) && ft_strlen(cmd) == 2)
		return(1);
	else if(!ft_strncmp(cmd,"pwd", 3) && ft_strlen(cmd) == 3)
		return(1);
	else if(!ft_strncmp(cmd,"echo", 4) && ft_strlen(cmd) == 4)
		return(1);
	else if(!ft_strncmp(cmd,"export", 6) && ft_strlen(cmd) == 6)
		return(1);
	return 0;
}

int ecxecuting_builtin(t_list *l)
{
	if(!(ft_strncmp(((t_all *)l->content)->ccmd[0],"cd", 2))
		&& ft_strlen(((t_all *)l->content)->ccmd[0]) == 2)
		change_path(((t_all *)l->content)->ccmd[1],((t_all *)l->content)->envp);
	else if(!(ft_strncmp(((t_all *)l->content)->ccmd[0],"pwd", 3))
			&& ft_strlen(((t_all *)l->content)->ccmd[0]) == 3)
			ft_pwd();
	// else if(!(ft_strncmp(((t_all *)l->content)->ccmd[0],"echo", 4))
	// 		&& ft_strlen(((t_all *)l->content)->ccmd[0]) == 4)
	// 		ft_echo(((t_all *)l->content)->ccmd);
	return(0);	
}

char *find_home(char **env)
{
	int i;
	int j;
	i = 0;
	j = 0;
	while(env[i])
    {
        if(ft_strncmp(env[i], "HOME=", 5) == 0)
            return(env[i] + 5);
        i++;
    }
	printf("cd: HOME not set");
	return(NULL);
}

int change_path(char *name_folder,char **env)
{
	char *new_path;

	new_path = getcwd(NULL,0);
	if (name_folder == NULL)
		new_path = find_home(env);
	else if(name_folder[0] == '/')
		new_path = name_folder;
	else
	{
		new_path = ft_strjoin(new_path,"/");
		new_path = ft_strjoin(new_path,name_folder);
	}
	// printf("->>>>>%s\n",new_path);
	chdir(new_path);
	// exit(0);
	return 0;
}