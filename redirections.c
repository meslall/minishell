/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 09:43:36 by zdasser           #+#    #+#             */
/*   Updated: 2022/05/27 18:12:32 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"minishell.h"



int	ft_count_infiles(char **s)
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
		while(s[i][j])
		{
			if(s[i][j] == '<' && s[i][j + 1] != '<')
				count++;
			j++;
		}
		i++;
	}
	return(count);
}

void	handle_multi(char *s, t_list *list)
{
	char *infile;
	int j = 0;
	int i = 0;
	int count = 0;
	while(s[j] && j + 1 <= (int)ft_strlen(s))
	{
		if(s[j] == '<' && s[j + 1] == '<')
			((t_all *)list->content)->hd = 1;
		else if (s[j] == '<' && s[j + 1] != '<' )
		{	
			
			i = j + 1;
			while(s[i] != 32 && s[i] != '\n' && s[i] != '<' && s[i])
				i++;
			infile = ft_substr(s, j + 1, i - 1);
			((t_all *)list->content)->inf[count] = open(infile, O_RDONLY);
			count++;
		} 
		
	j+= i;
	if(j > (int)ft_strlen(s))
		j = ft_strlen(s);
	}
	
}

void	check_redirections(t_list *list)
{
	int i;
	char **s;
	char *infile;
	int count;
	int redir = 0;

	i = 0;
	while(list)
	{
		i = 0;
		s = ((t_all *)list->content)->cmd;
		count = ft_count_infiles(s);
		if(count)
		{
			((t_all *)list->content)->inf = malloc(sizeof(int) * count);
		while(s[i])
		{
			printf("---%s----\n",s[i]);
			if(ft_cmp(s[i], '<') && ft_strlen(s[i]) == 1)
			{
				infile = s[i + 1];
				((t_all *)list->content)->inf[redir] = open(infile, O_RDONLY);
				i++;
				redir++;
			}
			else if (ft_strlen(s[i]) > 1 && ft_cmp(s[i], '<'))
				handle_multi(s[i], list);
			i++;
		}
		}
		else if (!count)
			((t_all *)list->content)->inf = (int *)ft_calloc(1, sizeof(int));
			
		list = list->next;
	}
}