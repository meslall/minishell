/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omeslall <omeslall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:10:11 by omeslall          #+#    #+#             */
/*   Updated: 2022/06/06 15:03:33 by omeslall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_isalnum(int c)
{
	if (48 <= c && c <= 57)
		return (1);
	else if ((65 <= c && c <= 90) || (97 <= c && c <= 122) || c == 32 
			|| c == '<' || c == '>' || c == '-')
		return (1);
	else
		return (0);
}

// int main()
// {
//     printf("%d\n",ft_isalnum(''));
// }
