/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:24:17 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/30 22:52:50 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	expand_split(t_list *exec,char *arg)
{
	char **tmp;
	char	*str;
	int	i;
	int len;

	i = -1;	
	tmp = ft_split(arg, ' ');
	while (tmp[++i])
	{
		len = len_2d_array((void **)(((t_data *)exec->content)->args));
		str = ft_strdup(tmp[i]);
		((t_data *)exec->content)->args = (char **)ft_2d_realloc((void **)(((t_data *)exec->content)->args),len + 1);
		((t_data *)exec->content)->args[len] = str;
	}
	
}