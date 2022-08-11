/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 20:45:36 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/11 18:27:42 by omeslall         ###   ########.fr       */
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
	data->inf = NULL;
	data->infiles = NULL;
	data->n_infiles = 0;
	data->outfiles = NULL;
	data->append = NULL;
	return (data);
}

// function realloc for int array
int		*ft_int_realloc(int *array, int len)
{
	int *new;
	int i;
	
	i = 0;
	new = malloc(sizeof(int) * (len + 1));
	while (i < len)
	{
		new[i] = array[i];
		i++;
	}
	new[i] = 0;
	free(array);
	return (new);
}