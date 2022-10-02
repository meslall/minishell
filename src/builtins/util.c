/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 19:49:14 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/28 20:05:07 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*norm_1(char **args, char *new_path, int mode)
{
	if (mode == 0)
	{
		new_path = ft_getenv("HOME=");
		if (new_path == NULL)
			new_path = ft_strdup(getenv("HOME"));
	}
	else if (mode == 1)
	{
		new_path = ft_strdup(args[1]);
	}
	else if (mode == 2)
	{
		new_path = ft_strjoin(new_path, "/");
		new_path = ft_strjoin(new_path, args[1]);
		g_glob.h_flag = 0;
	}
	else
	{
		g_glob.new_path = ft_getenv("PWD=");
		if (!g_glob.new_path)
			g_glob.h_flag = 1;
		g_glob.old_pwd = ft_strdup(g_glob.new_path);
	}
	return (new_path);
}

void	norm_2(char **args)
{
	khwi(g_glob.new_path);
	g_glob.new_path = norm_1(args, g_glob.new_path, 1);
}

void	khwi(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

int	err_chdir(char **args)
{
	char	*str;

	str = NULL;
	str = getcwd(NULL, 0);
	if (str == NULL)
		return (cd_err(), khwi(g_glob.new_path), khwi(g_glob.old_pwd), 0);
	err_cd(args, 1);
	khwi(str);
	return (1);
}
