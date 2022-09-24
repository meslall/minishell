/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:24:17 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/24 19:04:04 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	utils_expand_split(t_list *exec, char **tmp, int f)
{
	int	i;

	i = -1;
	if (f == 1 && len_2d_array((void *)tmp) != 1)
	{
		((t_data *)exec->content)->error = 1;
		while (tmp[++i])
			free(tmp[i]);
	}
	else if(f == 1 && len_2d_array((void *)tmp) == 1)
	{
		i = -1;
		while (tmp[++i])
			free(tmp[i]);
	}
}

void	expand_split(t_list *exec, char *arg, int f)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(arg, ' ');
	utils_expand_split(exec, tmp, f);
	while (f == 0 && tmp[++i])
	{
		((t_data *)exec->content)->args = (char **)ft_2d_realloc \
		((void **)(((t_data *)exec->content)->args), \
		len_2d_array((void **)(((t_data *)exec->content)->args))+ 1);
		((t_data *)exec->content)->args[len_2d_array \
		((void **)(((t_data *)exec->content)->args))] = ft_strdup(tmp[i]);
		free(tmp[i]);
	}
	free(tmp);
}

char	*fill_expand(t_list *exec, char *value)
{
	int	i;
	int	len;

	i = -1;
	(void)exec;
	value = ft_strjoin(value, "=");
	while (g_glob.envp[++i])
	{
		if (ft_strncmp(g_glob.envp[i], value, ft_strlen(value)) == 0)
		{
			len = ft_strlen(value);
			free(value);
			value = ft_strdup(g_glob.envp[i] + len);
			return (value);
		}
	}
	free(value);
	return (NULL);
}

void	expand_exit_status(char **tmp,int *i)
{
	char	*tmp1;

	tmp1 = ft_itoa(0);
	if (tmp1)
	{
		*tmp = ft_strjoin(*tmp, tmp1);
		free(tmp1);
	}
	*i += 1;
}
