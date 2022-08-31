/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 04:56:15 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/08/21 09:47:43 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_cmd(char **envp)
{
	char	*path;

	(void)envp;
	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	if (!path)
	{
		path = getenv("PWD");
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		free(path);
	return (0);
}
