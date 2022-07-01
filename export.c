/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadi <skadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:41:39 by skadi             #+#    #+#             */
/*   Updated: 2022/06/27 20:37:22 by skadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int calculate_size(char **s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return(i);
}

void    put_var(t_list *lenvp, t_var *var, char *c)
{
    int i;
	t_list *temp;
    char **s;
    int j;
    
	i = 0;
    s = var->name;
    j = calculate_size(s);
	while (i < j)
	{
        if (!ft_strncmp(var->name[i], c, ft_strlen(var->name[i])))
        {
            temp = ft_lstnew(var->name[i]);
            ft_lstadd_back(&lenvp,temp);
        }
        i++;
	}
}


int check_var_exist(char *s, t_var *var)
{
    int i;

    i = 0;
    while (var->name[i])
	{
        if (!ft_strncmp(var->name[i], s, ft_strlen(s)))
            return(1);
        i++;
	}
    return(0);
}

void get_var_value(char *s, t_var *data)
{
    int n;

    n = data->i;
    if(n == 0)
        data->name[n] = s;
    else
    {
        data->name = realloc_char(data->name, n + 2);
        data->name[n] = s;
    }
    data->i++;
}

void get_dec(char *s, t_var *data)
{
    if(!s)
        return;
     if(ft_cmp(s, '='))
        get_var_value(s, data);
}

int ft_export(t_list *l, t_var *data)
{
    int i;
    char **s;
    int count;

    count = 0;
    i = 0;
    while(l)
    {
        s = ((t_all *)(l->content))->ccmd;
        while(s[i] && s[i + 1])
        {
            if(ft_strcmp(s[i], "export"))
            {
                count++;
                if (!check_var_exist(s[i + 1], data))
                    get_dec(s[i + 1], data);
                put_var(((t_all *)(l->content))->lenvp, data, s[i + 1]);
            }
            i++;
        }

        l = l->next;
    }
    return(count);
}


int var_dec(t_list *l, t_var *data)
{
    char **s;
    int i;
    int j;

    i = 0;
    j = 0;
    s = ((t_all *)(l->content))->ccmd;
    if(calculate_size(s) == 1)
    {
        if(ft_strcmp(s[0], "="))
        {
            get_var_value(s[0], data);
            return(0);
        }
    }
    else
       j = ft_export(l, data);
    return(j);
}
