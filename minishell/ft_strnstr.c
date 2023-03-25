/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:23:43 by hyounsi           #+#    #+#             */
/*   Updated: 2023/03/18 16:15:07 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len_little ;

	i = 0;
	if (!big && len == 0)
		return (NULL);
	len_little = ft_strlen(little);
	if (len_little == 0)
		return ((char *)big);
	while (*(big + i) && i < len)
	{
		j = 0;
		k = i;
		while (*(big + k + j) == *(little + j) && *(big + k + j) && k + j < len)
		{
			j++;
			if (len_little == j)
				return ((char *)big + k);
		}
		i++;
	}
	return (NULL);
}
