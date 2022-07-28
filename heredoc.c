/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:04:34 by zdasser           #+#    #+#             */
/*   Updated: 2022/07/25 20:32:41 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_delimiter(t_list *l, char *s, int *count)
{
	int	i;
	int j;
	char *delimiter;
	
	i = 0;
	j = 0;
	delimiter = NULL;
	while (s[i] && i + 1 <= (int)ft_strlen(s))
	{
		if (s[i] == '<' && s[i + 1] == '<' && ft_strlen(s) > 2)
		{
			j = i + 2;
			while (s[j] != 32 && s[j] != '\n' && s[j] != '<' && s[j] && s[j] != '>')
				j++;
			delimiter = ft_substr(s, i + 2, j);
			take_quotes(delimiter, 39);
			take_quotes(delimiter, '"');
			((t_all *)(l->content))->delimiter[*count] = delimiter;
		    *count+= 1;
			if (s[j] == '<' && s[j + 1] == '<' && s[j + 2] == '\0')
				return (1);
		}
		if (j)
			i += j - 1;
		i++;
		if (i > (int)ft_strlen(s))
			i = ft_strlen(s);
	}
	return (0);
}

void cmd_loop(t_list *l)
{
	char **s;
	int	i;
	int j;
	int count;
	char *delimiter;
	while (l)
	{
		delimiter = NULL;
		count = 0;
		((t_all *)l->content)->delimiter = malloc(sizeof(char *) * ((t_all *)l->content)->hd + 1);
		i = 0;
		j = 0;
		s = ((t_all *)l->content)->cmd;
		while (s && s[i])
		{
			if (ft_cmp(s[i], '<'))
			{
				if ( ft_strlen(s[i]) == 2 && s[i][j] == '<' && s[i][j + 1] == '<')
				{
					if(ft_cmp(s[i + 1],'<'))
					{
						while (s[i + 1][j] != 32 && s[i + 1][j] != '\n' && s[i + 1][j] != '<' 
								&& s[i + 1][j] && s[i + 1][j] != '>')
						j++;
						delimiter = ft_substr(s[i + 1], 0, j);
						get_delimiter(l, *s + j, &count);
					}
					else
						delimiter = s[i + 1];//<< f<<a
					((t_all *)l->content)->delimiter[count] = delimiter;
					count++;
				}
				else
				{
					if(get_delimiter(l, s[i], &count))
						printf("##############\n");
						// get_delimiter(l, s[i + 1], &count);
				}
			}
			i++;
		}
		((t_all *)l->content)->delimiter[count] = NULL;
		count = 0;
		while (((t_all *)l->content)->delimiter[count])
		{
			printf("---------> : %s\n", ((t_all *)l->content)->delimiter[count]);
			count++;
		}
		l = l->next;
    }
}

void	check_heredoc(t_list *l)
{
	int i;
	int j;
	char *c;
	char *tmp;
	char *line;
	char *input;
	int fd[2];
	char **split_line;

	c = ft_strdup("\a");
	tmp = NULL;
	line = "";
    cmd_loop(l);
	while (l)
	{
		i = 0;
		j = ((t_all *)l->content)->hd;
		if (j)
		{
			while (i < j)
			{
				input = readline("heredoc>");
				while (!ft_strcmp(input, ((t_all *)l->content)->delimiter[i]))
				{
					if(!input[0])
						input = ft_strdup(" ");
				    tmp = ft_strjoin(input, c);
					line = ft_strjoin(line, tmp);
					free(input);
					free(tmp);
					input = readline("heredoc>");
				}
				i++;
			}
			split_line = ft_split(line, *c);
			pipe(fd);
			i = 0;
			while(split_line[i])
			{
				ft_putstr_fd(split_line[i], fd[1]);  
				ft_putstr_fd("\n", fd[1]);
				i++;
			}
			close(fd[1]);
			((t_all *)l->content)->fd = fd[0];
			free(split_line);
		}
		l = l->next;
	}
	free(c);
}
