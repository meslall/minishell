/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 09:59:48 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/31 19:41:42 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0')
		return (1);
	return (0);
}

int check_if_expand(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	next_expand(char *s)
{
	int i;

	i = 0;
	if (s[0] == '$')
		i++;
	while (s[i])
	{
		if ((s[i] >= 32 && s[i] <= 47 )|| (s[i] >= 58 && s[i] <= 64 ) 
		|| (s[i] >= 91 && s[i] <= 96 ) || (s[i] >= 123 && s[i] <= 126 ) )//32–47 / 58–64 / 91–96 / 123–126
			return (i);
		i++;
	}
	return (i);
}

void	expand(t_list *exec,char *value,char **arg)
{
	int		i;
	char	*tmp;
	char	*tmp1;
	char	*c;
	int 	j;

	j = 0;
	tmp = ft_strdup("");
	c = ft_strdup(" ");
	i = 0;
	while(value[i])
	{
		if(value[i] == '$' && is_white_space(value[i + 1]) == 0)
			{
				j = next_expand(&value[i]) + i;
				tmp1 = fill_expand(exec,ft_substr(value,i + 1,j));
				if(tmp1)
				{
					tmp =ft_strjoin(tmp ,tmp1);
					free(tmp1);					
				}
				if(j <= (int)ft_strlen(value))
					i = j - 1;
			}
		else
		{
			c[0] = value[i];
			tmp = ft_strjoin(tmp,c);
		}
		i++;
	}
	*arg = ft_strdup(tmp);
	free(tmp);
}

char	*fill_expand(t_list *exec,char *value)
{
	int i;

	i = -1;
	value = ft_strjoin(value,"=");
	while (((t_data *)exec->content)->envp[++i])
	{
		if(ft_strncmp(((t_data *)exec->content)->envp[i],value,ft_strlen(value)) == 0)
		{
			value = ft_strdup(((t_data *)exec->content)->envp[i] + ft_strlen(value));
			return(value);
		}
	}
	return (NULL);	
}
