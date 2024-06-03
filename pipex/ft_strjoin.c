/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:10:01 by aazra             #+#    #+#             */
/*   Updated: 2022/04/02 15:01:56 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char		*result;
	size_t		size_s1;
	size_t		size_s2;

	if (!(s1) && !(s2))
		return (0);
	else if (!(s1) || !(s2))
	{
		if (!s1)
			return (ft_strdup(s2));
		if (!s2)
			return (ft_strdup(s1));
	}
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	result = malloc(sizeof(*result) * (size_s1 + size_s2 + 1));
	if (!result)
		return (0);
	ft_strlcpy(result, s1, size_s1 + 1);
	ft_strlcat(result + size_s1, s2, size_s2 + 1);
	return (result);
}
