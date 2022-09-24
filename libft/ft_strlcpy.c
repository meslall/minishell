/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 20:50:32 by omeslall          #+#    #+#             */
/*   Updated: 2022/09/24 17:29:40 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	j;
	size_t	i;

	i = 0;
	while (src[i])
		i++;
	if (n == 0)
		return (i);
	j = 0;
	printf("src %s \n", dest);
	while (src[j] != '\0' && j < n - 1)
	{
		printf("inside loop \n");
		dest[j] = src[j];
		j++;
		printf("inside loop2 \n");
	}
	dest[j] = '\0';
	return (i);
}
