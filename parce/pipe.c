/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 22:05:12 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/09 22:06:31 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../src/minishell.h"

void	fill_pipe(t_list *exec)
{
	t_list *new;
	
	new  =  init_execution();
	ft_lstadd_back(&exec, new);
}