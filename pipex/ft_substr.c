/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:11:58 by aazra             #+#    #+#             */
/*   Updated: 2022/03/22 11:53:00 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*result;
	unsigned int	i;
	size_t			size_s;

	i = 0;
	if (!s)
		return (0);
	size_s = ft_strlen(s);
	if (start >= size_s)
		return (ft_strdup("\0"));
	result = malloc(sizeof(*result) * (len + 1));
	if (!result)
		return (0);
	while (i < len)
	{
		result[i] = s[start];
		i++;
		start++;
	}
	result[i] = '\0';
	return (result);
}
