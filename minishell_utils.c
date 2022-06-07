/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 19:07:56 by omeslall          #+#    #+#             */
/*   Updated: 2022/06/06 15:58:16 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void converter(char **envp,t_all *all)
{
	int i;
	t_list *temp;
	t_list *a;

	a = NULL;
	i = 0;
	while (envp[i])
	{
		temp = ft_lstnew(envp[i]);
		ft_lstadd_back(&a,temp);
		i++;
	}
	all->lenvp = a;
}

t_all *ft_init(t_all *all)
{
	t_all	*temp;

	temp = malloc(sizeof(t_all));
	temp->envp = all->envp;
	temp->lenvp = all->lenvp;
	return(temp);
}

int check_qoute(char *str)
{
	int i = 0;
	
	while (str[i])
	{
		if(str[i] == '"' || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

char *ft_redi(char *str, int *a)
{
	int i = 0;
	int closed = 0;
	char temp;
	char *c;
	char *s;

	closed = 0;
	i = 0;
	s = ft_strdup(" ");
	c = ft_strdup(" ");
	while (str[i])
	{
		if(*a == 1)
		{
			*a = 0;
			break;
		}
		
		if(str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			if (closed == 2)
				closed = 0;
			if(closed == 0)
				temp = str[i];
			if(closed == 0 || temp == str[i])
				closed++;
		}
		if(str[i] == '>' && (closed == 0  || closed == 2))
		{
			if(str[i + 1] == '\0')
				*a = 1;
			break;		
		}
		else if(str[i] == '<' && (closed == 0  || closed == 2))
		{
			if(str[i + 1] == '\0')
				*a = 1;
			break;
		}
		c[0] = str[i];
		s = ft_strjoin(s, c);
		i++;
	}
	// printf("in : %s\n",s);
	return(s);
}

char **ft_ccmd(char **cmd)
{
	int i;
	int a;
	char *temp;
	
	i = 0;
	a = 0;
	temp = ft_strdup(" ");
	while (cmd[i])
	{
		// printf("before : %s\n",cmd[i]);
		temp = ft_strjoin(temp, ft_redi(cmd[i],&a));
		// printf("after : %s\n",temp);
		i++;
	}
	return (ft_split(temp,' '));
 }
