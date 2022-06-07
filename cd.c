/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:26:54 by omeslall          #+#    #+#             */
/*   Updated: 2022/05/30 21:20:14 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_builtin(char *cmd)
{
	if(!(ft_strncmp(cmd,"cd",2)) && ft_strlen(cmd) == 2)
		return(1);

	return 0;
}

int	slash(char *str)
{
	int i;
	int count;
	
	count = 0;
	i = 0;
	while (str[i])
	{
		if(str[i] == '/')
			count++;
		if(count == 3)
			return(i);
		i++;
	}
	return (0);
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
	else
	{
		new_path = ft_strjoin(new_path,"/");
		new_path = ft_strjoin(new_path,name_folder);
	}
	chdir(new_path);
	return 0;
}