/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qaout_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:35:40 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/24 17:31:23 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	utils1_qaout(t_list *exec, char **tmp, char **arg)
{
	int		len;
	char	*tmp1;

	len = 0;
	tmp1 = *tmp;
	*tmp = ft_strjoin(*arg, *tmp);
	free(tmp1);
	expand(exec, *tmp, arg);
	expand_split(exec,*arg, 0);
	len = len_2d_array((void **)(((t_data *)exec->content)->args));
	free(*arg);
	if (len > 0)
	{
		*arg = ft_strdup(((t_data *)exec->content)->args[len - 1]);
		free(((t_data *)exec->content)->args[len]);
		free(((t_data *)exec->content)->args[len - 1]);
		((t_data *)exec->content)->args[len - 1] = NULL;
	}
	else
		*arg = ft_strdup("");
}

void	qaout(t_list *exec, char *value, char **arg, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	if ((int)ft_strlen(value) <= i)
	{
		position_quote(value, 1);
		return ;
	}
	j = position_quote(value, 0);
	tmp = ft_substr(value, i, j);
	if (check_qaout(tmp) == 1)
		single_quote(tmp, arg, 0);
	else if (check_qaout(tmp) == 2)
		double_quote(exec, tmp, arg, 0);
	else if (check_if_expand(tmp))
		utils1_qaout(exec, &tmp, arg);
	else
		*arg = ft_strjoin(*arg, tmp);
	free(tmp);
	qaout(exec, value, arg, j);
}
