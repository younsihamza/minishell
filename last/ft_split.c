/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyounsi <hyounsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:57:29 by hyounsi           #+#    #+#             */
/*   Updated: 2023/03/27 14:56:41 by hyounsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	freemem(char **array, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(array[i++]);
	}
	free(array);
	array = NULL ;
	return (1);
}

static int	number_of_word(char const *s, char c)
{
	int	i;
	int	size_of_each ;
	int	now;

	now = 0;
	i = 0;
	while (*(s + i))
	{
		size_of_each = 0;
		while (*(s + i) == c && *(s + i))
			i++;
		while (*(s + i) != c && *(s + i))
		{
			i++;
			size_of_each++;
		}
		if (size_of_each != 0)
			now++;
	}
	return (now);
}

static int	size_of_word(char **array, char c, char const *s)
{
	int	i;
	int	j;
	int	size_of_each;

	i = 0;
	j = 0;
	while (*(s + i))
	{
		size_of_each = 0;
		while (*(s + i) == c && *(s + i))
			i++;
		while (*(s + i) != c && *(s + i))
		{
			i++;
			size_of_each++;
		}
		if (size_of_each != 0)
		{
			array[j] = ft_calloc(sizeof(char), size_of_each + 1);
			if (!array[j])
				return (freemem(array, j));
			j++;
		}
	}
	return (0);
}

static void	fill_substr(char **array, char c, char const *s)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	i = 0;
	while (*(s + i))
	{
		k = 0;
		while (*(s + i) == c && *(s + i))
			i++;
		while (*(s + i) != c && *(s + i))
		{
			array[j][k] = *(s + i);
			i++;
			k++;
		}
		if (k != 0)
		{
			j++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	int		n;
	char	**array;
	int		a;

	if (s == NULL)
		return (NULL);
	n = number_of_word(s, c);
	array = ft_calloc(sizeof(char *), n + 1);
	if (!array)
		return (NULL);
	a = size_of_word(array, c, s);
	if (a == 1)
		return (NULL);
	fill_substr(array, c, s);
	return (array);
}
