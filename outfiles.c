/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skadi <skadi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 11:15:47 by zdasser           #+#    #+#             */
/*   Updated: 2022/06/24 22:08:32 by skadi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_outfiles(char **s)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;

	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == '>' && s[i][j + 1] != '>')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	handle_long(char *s, t_list *list)
{
	char *outfile;
	int j = 0;
	int i = 0;
	int count = 0;
	
	while (s[j] && j + 1 <= (int)ft_strlen(s))
	{
		if (s[j] == '>' && s[j + 1] != '>' )
		{
			i = j + 1;
			while (s[i] != 32 && s[i] != '\n' && s[i] != '>' && s[i])
				i++;
			outfile = ft_substr(s, j + 1, i - 1);
			((t_all *)list->content)->outf[count] = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0755);
			free(outfile);
			count++;
		}
		if (s[j] == '>' && s[j + 1] == '>' )
		{
			i = j + 2;
			while (s[i] != 32 && s[i] != '\n' && s[i] != '>' && s[i])
				i++;
			outfile = ft_substr(s, j + 2, i - 1);
			((t_all *)list->content)->outf[count] = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0755);
			free(outfile);
			count++;
		}
		
	if(i > 0)
		j+= i - 1;
	j++;
	if(j > (int)ft_strlen(s))
		j = ft_strlen(s);
	}
	
}


void handle_multi_outfiles(char **s, t_list *list, int *count)
{
	int i;
	int	j;
	char *outfile;

	i = 0;
	while (s[i])
	{
		
		j = 0;
		
		if (ft_strlen(s[i]) == 2 && s[i][j] == '>' && s[i][j + 1] == '>')
		{
				outfile = s[i + 1];
				((t_all *)list->content)->outf[*count] = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0755);
				*count += 1;
				i++;
		}
		else
			handle_long(s[i], list); 
			
		i++;
	}
}

void	check_outfiles(t_list *list)
{
	int i;
	char **s;
	int count;
	int redir = 0;

	while (list)
	{
		       
		s = ((t_all *)list->content)->cmd;
		count = ft_count_outfiles(s);
		if (count)
		{
			i = count;
			((t_all *)list->content)->outf = malloc(sizeof(int) * count);
			((t_all *)list->content)->n_outf = count;
			handle_multi_outfiles(s, list, &redir);
		}
		 
		else if (!count)
		{
			((t_all *)list->content)->outf = (int *)ft_calloc(1, sizeof(int));
			count++;
			while (count--)
				((int *)((t_all *)list->content)->outf )[count] = 1;
		}
		list = list->next;
	}
}
