/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:38:14 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/24 16:39:16 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	utils4_qaout_in_redi(char **tmp, char **value)
{
	free(*tmp);
	free(*value);
}

void	fill_outfile(t_list *exec, t_token *token)
{
	((t_data *)exec->content)->outfiles = (char **)ft_2d_realloc \
	((void **)(((t_data *)exec->content)->outfiles), \
	len_2d_array((void **)(((t_data *)exec->content)->outfiles)) + 1);
	((t_data *)exec->content)->outfiles[len_2d_array \
	((void **)(((t_data *)exec->content)->outfiles))] = ft_strdup(token->value);
}

void	fill_append(t_list *exec, t_token *token)
{
	parse_arg_redi(token, exec);
	((t_data *)exec->content)->append = (char **)ft_2d_realloc \
	((void **)(((t_data *)exec->content)->append), \
	len_2d_array((void **)(((t_data *)exec->content)->append)) + 1);
	((t_data *)exec->content)->append[len_2d_array \
	((void **)(((t_data *)exec->content)->append))] = ft_strdup(token->value);
}
