/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:09:20 by aazra             #+#    #+#             */
/*   Updated: 2022/03/22 11:49:34 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**arr_free(char **ptr, unsigned int k)
{
	unsigned int	i;

	i = 0;
	while (i < k)
	{
		if (ptr[i])
			free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static unsigned int	cnt_w(char *s, char c)
{
	unsigned int	count;
	unsigned int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**prereq(char *s, char c)
{
	char			**ptr;

	if (!s)
		return (NULL);
	ptr = (char **)malloc((cnt_w((char *)s, c) + 1) * sizeof(*ptr));
	if (!ptr)
		return (NULL);
	return (ptr);
}

char	**split_2(char **ptr, int k)
{
	ptr[k] = NULL;
	return (ptr);
}

char	**ft_split(char *s, char c)
{
	char			**ptr;
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;

	i = 0;
	k = 0;
	ptr = prereq(s, c);
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (s[j])
			ptr[k] = ft_substr((char *)s, j, i - j);
		if (!ptr[k])
			return (arr_free(ptr, k));
		if (s[j])
			k++;
	}
	return (split_2(ptr, k));
}
