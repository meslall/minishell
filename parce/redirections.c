/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 00:33:34 by omeslall          #+#    #+#             */
/*   Updated: 2022/08/11 17:13:11 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../src/minishell.h"

void	fill_redirections(t_list *exec, t_token **token, t_lexer *lexer)
{
	if ((*token)->type == L_REDIRECTION)
	{
		free_token(*token);
		*token = get_next_token(lexer);
		if((*token)->type == ARG && ((t_data *)exec->content)->error != 1)
			fill_infile(exec, *token);
	}
	// else if (token->type == R_REDIRECTION)
	// {
	// 	((t_data *)exec->content)->redirections[1] = token->value;
	// 	((t_data *)exec->content)->redirections[0] = NULL;
	// }
}

void	fill_infile(t_list *exec, t_token *token)
{
	int	fd;
	
	fd = open(token->value, O_RDONLY);
	if (fd == -1)
	{
		((t_data *)exec->content)->inf = ft_strdup(token->value);
		((t_data *)exec->content)->error = 1;
	}
	((t_data *)exec->content)->infiles = ft_int_realloc(((t_data *)exec->content)->infiles, ((t_data *)exec->content)->n_infiles);
	((t_data *)exec->content)->infiles[((t_data *)exec->content)->n_infiles] = fd;
	((t_data *)exec->content)->n_infiles++ ;
	
}