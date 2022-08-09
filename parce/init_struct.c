/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:45:36 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/09 20:58:13 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../src/minishell.h"

t_list	*init_execution()
{
	t_list *exec;
	
	exec = malloc(sizeof(t_list));
    exec->content = init_data();
	exec->next = NULL;
	return (exec);
}

t_data	*init_data()
{
	t_data *data;
	
	data = malloc(sizeof(t_data));
	data->args = NULL;
	data->error = 0;
	return (data);
}