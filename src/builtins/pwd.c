/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 04:56:15 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/09/28 18:17:06 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_cmd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (s == NULL)
	{
		s = ft_getenv("PWD=");
		if (s == NULL)
			printf("%s\n", g_glob.pwd);
		else
			printf("%s\n", s);
	}
	else
		printf("%s\n", s);
	free(s);
	return (0);
}
