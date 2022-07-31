/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 11:19:51 by skadi             #+#    #+#             */
/*   Updated: 2022/07/31 22:35:33 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_var(t_list *lenvp, char **var)
{
    char    *content;
    char    *tmp;
    int     i;
    int     j;
    char    **tab;
    t_list  *tmp_env;

    i = -1;
    j = 0;
    tmp = "";
    tab = ft_split(*var, '$');
    while (tab[++i])
        tab [i] = ft_strjoin("$", tab[i]);
    i = -1;
    while (tab[++i])
        tab[i] = ft_strjoin(tab[i], "=");
    i = 0;
    tmp_env = lenvp;
    while(tab[i])
    {
        while(lenvp)
        {
            content = ((char *)(lenvp->content));
            if (!ft_strncmp(content, tab[i] + 1, ft_strlen(tab[i]) - 1))
            {
                    *var = content + ft_strlen(tab[i]) - 1;
                    tmp = ft_strjoin(tmp, *var);
            }
            lenvp = lenvp->next;
        }
        lenvp = tmp_env;
        i++;
    }
    *var = tmp;
}

void check_var(t_list *l)
{
    char    **s;
    int     i;

    while(l)
    {
        i = 0;
        s = ((t_all *)(l->content))->ccmd;
        while(s[i])
        {
            if(ft_cmp(s[i], '$'))
				get_var(((t_all *)(l->content))->lenvp, &s[i]);
            i++;
        }
        l = l->next;
    }
}