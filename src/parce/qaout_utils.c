/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qaout_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:32:46 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/24 16:38:38 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

int	position_quote_s(char *s, int f)
{
	static int	i;

	while (s[i])
	{
		if (s[i] == '\'')
			return (i++);
		i++;
	}
	if (f == 1)
		i = 0;
	return (i);
}

void	single_quote(char *value, char **arg, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	j = position_quote_s(value, 0);
	if ((int)ft_strlen(value) < i)
	{
		position_quote_s(value, 1);
		return ;
	}
	tmp = ft_substr(value, i, j);
	*arg = ft_strjoin(*arg, tmp);
	free(tmp);
	single_quote(value, arg, j + 1);
}

int	position_quote_d(char *s, int f)
{
	static int	i;

	while (s[i])
	{
		if (s[i] == '"')
			return (i++);
		i++;
	}
	if (f == 1)
		i = 0;
	return (i);
}

void	double_quote(t_list *exec, char *value, char **arg, int i)
{
	char	*tmp;
	char	*tmp1;
	int		j;
	int		q;

	j = 0;
	q = 0;
	j = position_quote_d(value, 0);
	if ((int)ft_strlen(value) < i)
	{
		position_quote_d(value, 1);
		return ;
	}
	tmp = ft_substr(value, i, j);
	if (check_if_expand(tmp) && ((t_data *)(exec->content))->if_hd != 1)
	{
		tmp1 = tmp;
		expand(exec, tmp, &tmp);
		free(tmp1);
	}
	*arg = ft_strjoin(*arg, tmp);
	free(tmp);
	double_quote(exec, value, arg, j + 1);
}
