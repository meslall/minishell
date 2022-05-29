/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:21:14 by omeslall          #+#    #+#             */
/*   Updated: 2022/05/23 23:51:20 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	flag;
	int	qout;
	int type;
    char temp;

	qout = type = 0;
	i = 0;
	flag = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == 39)
		{
			if(type != 0 && s[i] == temp)
				qout++;
			if(s[i] == '"' && type == 0)
				{
                    temp = s[i];
					qout++;
					type = 2;
				}
			else if(s[i] == 39 && type == 0)
				{
                    temp = s[i];
					qout++;
					type = 1;
				}
		}
		else if (s[i] != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (s[i] == c && (qout == 2 || qout == 0))
		{
			flag = 0;
			qout = 0;
			type = 0;
		}
		i++;
	}
	return (count);
}

static char	*word_in(char const *s, int start, int end)
{
	int		i;
	int		size;
	char	*word;

	i = 0;
	size = end - start;
	word = malloc((size + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < end)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static char	**memory(char const *s, char c)
{
	int		i;
	int		size;
	char	**array;

	i = 0;
	size = count_words(s, c);
	array = malloc((size + 1) * sizeof(char *));
	if (!s[i] && !array)
	{
		free(array);
		return (0);
	}
	return (array);
}

static char	**itre(char const *s, char c, char **array)
{
	int		size;
	int		i;
	int		j;
	int		k;
	int		qoute;
	char	temp;
	int		type;

	type = 0;
	k = -1;
	j = 0;
	i = 0;
	qoute = 0;
	size = ft_strlen(s);
	while (i <= size)
	{
		if (s[i] == '"' || s[i] == 39)
		{
			if(type != 0 && s[i] == temp)
				qoute++;
			if(s[i] == '"' && type == 0)
				{
                    temp = s[i];
					qoute++;
					type = 2;
				}
			else if(s[i] == 39 && type == 0)
				{
                    temp = s[i];
					qoute++;
					type = 1;
				}
		}
		if (s[i] != c && k < 0)
			k = i;
		else if ((s[i] == c || i == size) && k >= 0 && (qoute == 0 || qoute == 2))
		{
			array[j] = word_in(s, k, i);
			k = -1;
			qoute = 0;
			type = 0;
			j++;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = memory(s, c);
	if (!array)
		return (NULL);
	return (itre(s, c, array));
}
