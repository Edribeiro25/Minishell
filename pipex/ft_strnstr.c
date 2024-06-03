/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazra <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:11:17 by aazra             #+#    #+#             */
/*   Updated: 2022/03/22 11:52:48 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	unsigned int	n;
	size_t			len_little;

	if (*little == '\0')
		return ((char *)(big));
	n = 0;
	len_little = ft_strlen(little);
	while (*big != '\0')
	{
		if (n + len_little > len)
			return (NULL);
		if (ft_strncmp(big, little, len_little) == 0)
			return ((char *)(big));
		big++;
		n++;
	}
	return (0);
}
