/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 19:07:56 by omeslall          #+#    #+#             */
/*   Updated: 2022/05/22 21:56:57 by omeslall         ###   ########.fr       */
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
