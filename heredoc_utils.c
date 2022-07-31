/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoulyaz <kdoulyaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 23:05:53 by kdoulyaz          #+#    #+#             */
/*   Updated: 2022/07/31 23:06:06 by kdoulyaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *h_get_var(t_list *lenvp, char **var)
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
    return (*var);
}

char *h_check_var(t_list *env, char *l)
{
    if(l[0] == '$')
		return (h_get_var(((t_all *)(env->content))->lenvp, &l));
    return (l);
}