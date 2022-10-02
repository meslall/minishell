/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 05:14:19 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/28 20:05:49 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_env(char *old_pwd, char *new_path)
{
	int	i;

	i = 1;
	new_path = ft_join1(ft_strdup("PWD="), ft_strdup(new_path));
	old_pwd = ft_join1(ft_strdup("OLDPWD="), ft_strdup(old_pwd));
	while (g_glob.envp[++i])
	{
		if (!ft_strncmp(g_glob.envp[i], "PWD=", 4))
		{
			free(g_glob.envp[i]);
			g_glob.envp[i] = ft_strdup(new_path);
			break ;
		}
	}
	while (g_glob.envp[++i])
	{
		if (!ft_strncmp(g_glob.envp[i], "OLDPWD=", 7))
		{
			free(g_glob.envp[i]);
			g_glob.envp[i] = ft_strdup(old_pwd);
			break ;
		}
	}
	free(new_path);
	free(old_pwd);
}

int	err_cd(char **args, int flag)
{		
	if (flag == 1)
	{
		write(2, "minishell: cd: ", 15);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": No such file or directory\n", 28);
		g_glob.g_exit_status = 1;
	}
	else
	{
		free(g_glob.new_path);
		free(g_glob.old_pwd);
		write(2, "minishell: cd: HOME not set\n", 28);
	}
	return (1);
}

int	cd_cmd(char **args)
{
	norm_1(args, g_glob.new_path, 3);
	if (args[1] == NULL || ((args[1][0] == '~') && ft_strlen(args[1]) == 1))
	{
		if (g_glob.h_flag == 1 && args[1] == NULL)
			return (err_cd(args, 0));
		free(g_glob.new_path);
		g_glob.new_path = norm_1(args, g_glob.new_path, 0);
	}
	else if (args[1][0] == '/')
		norm_2(args);
	else
		g_glob.new_path = norm_1(args, g_glob.new_path, 2);
	if (chdir(g_glob.new_path) == -1)
	{
		if (err_chdir(args) == 0)
			return (0);
	}
	update_env(g_glob.old_pwd, g_glob.new_path);
	return (khwi(g_glob.new_path), khwi(g_glob.old_pwd), g_glob.g_exit_status);
}

int	cd_cmd1(char **args)
{
	g_glob.new_path = ft_strdup(g_glob.pwd);
	g_glob.old_pwd = ft_strdup(g_glob.new_path);
	if (args[1] == NULL || ((args[1][0] == '~') && ft_strlen(args[1]) == 1))
	{
		if (g_glob.h_flag == 1 && args[1] == NULL)
			return (err_cd(args, 0));
		free(g_glob.new_path);
		g_glob.new_path = norm_1(args, g_glob.new_path, 0);
	}
	else if (args[1][0] == '/')
		norm_2(args);
	else
		g_glob.new_path = norm_1(args, g_glob.new_path, 2);
	if (chdir(g_glob.new_path) == -1)
	{
		if (err_chdir(args) == 0)
			return (0);
	}
	update_env1(g_glob.old_pwd);
	khwi(g_glob.pwd);
	g_glob.pwd = ft_strdup(g_glob.new_path);
	return (free(g_glob.new_path), khwi(g_glob.old_pwd), g_glob.g_exit_status);
}
