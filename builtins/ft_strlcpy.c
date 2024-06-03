/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:10:26 by aazra             #+#    #+#             */
/*   Updated: 2022/04/04 23:56:51 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	count;

	count = 0;
	if (!(src) || !(dst))
		return (0);
	if (size > 0)
	{
		while (--size && src[count])
		{
			dst[count] = src[count];
			count++;
		}
		dst[count] = '\0';
	}
	while (src[count])
		count++;
	return (count);
}

void	cder(char *l)
{
	char	*s;
	char	*s1;

	s = ft_strjoin("Minishell: cd: ", l);
	s1 = ft_strjoin(s, ": ");
	free(s);
	s = ft_strjoin(s1, strerror(errno));
	free(s1);
	s1 = ft_strjoin(s, "\n");
	write(2, s1, ft_strlen(s1));
	free(s1);
	free(s);
}

char	*sdol(int *i)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * 2);
	if (!tmp)
		return (NULL);
	tmp[0] = '$';
	tmp[1] = '\0';
	*i = *i + 1;
	return (tmp);
}
