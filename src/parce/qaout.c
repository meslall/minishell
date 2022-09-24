/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qaout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:59:02 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/24 16:36:06 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	utils1_position_quote(int f, int *i, int *q, char *tmp)
{
	if (f == 1)
	{
		*i = 0;
		*q = 0;
		*tmp = '\0';
	}
}

int	utils2_position_quote(int j, int *i, int *q, char *tmp)
{
	*tmp = '"';
	*q += 1;
	*i += 1;
	j = *i - 1;
	return (j);
}

int	utils3_position_quote(int j, int *i, int *q, char *tmp)
{
	*tmp = '\'';
	*q += 1;
	*i += 1;
	j = *i - 1;
	return (j);
}

int	position_quote(char *s, int f)
{
	static int	i;
	static int	q;
	static char	tmp;
	int			j;

	j = 0;
	while (s[i])
	{
		if (s[i] == '"' && q == 0)
			return (utils2_position_quote(j, &i, &q, &tmp));
		else if (s[i] == '\'' && q == 0)
			return (utils3_position_quote(j, &i, &q, &tmp));
		else if (s[i] == tmp && q == 1)
		{
			tmp = '\0';
			q = 0;
			return (i++);
		}
		i++;
	}
	utils1_position_quote(f, &i, &q, &tmp);
	return (i);
}
