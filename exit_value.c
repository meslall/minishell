/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:05:16 by zdasser           #+#    #+#             */
/*   Updated: 2022/06/14 12:25:57 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"minishell.h"

int check_dollar(t_list *l)
{
	int i;
	char *s;

	i = 0;

	if (!l)
		return(0);
	if (ft_strcmp(((t_all *)l->content)->cmd[0], "$?"))
	{
		s = ((t_all *)l->content)->cmd[0];
		while(s[i] && i + 1<= (int)ft_strlen(s))
		{
			while(s[i] != '$' && s[i + 1] != '?' && s[i])
			{
				printf("%c\n", s[i]);
				i++;
			}
			if(s[i] == '$' && s[i + 1] == '?')
				printf("%i : command not found\n", *sttc_var());
			i += 2;
		}
		return(1);
	}
	return(0);
}