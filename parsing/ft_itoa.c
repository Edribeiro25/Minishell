/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 13:26:49 by user42            #+#    #+#             */
/*   Updated: 2022/04/05 12:42:29 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static unsigned int	ft_nblen(int n)
{
	unsigned int	i;
	unsigned int	nb;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	i = 0;
	while (nb >= 10)
	{
		nb /= 10;
		i++;
	}
	return (i + 1);
}

char	*ft_sign_malloc(int n)
{
	char			*dest;
	unsigned int	len;

	dest = NULL;
	len = ft_nblen(n);
	dest = malloc(sizeof(*dest) * len + 1);
	if (dest == NULL)
		return (NULL);
	return (dest);
}

char	*ft_itoa_comp(char *dest, unsigned int *nb, unsigned int *i)
{
	dest[(*i)--] = *nb % 10 + 48;
	*nb /= 10;
	return (dest);
}

char	*ft_itoa(int n)
{
	char			*dest;
	unsigned int	nb;
	unsigned int	len;
	unsigned int	i;

	dest = ft_sign_malloc(n);
	if (dest == NULL)
		return (NULL);
	len = ft_nblen(n);
	i = 0;
	nb = n;
	i = len - 1;
	while (nb >= 10)
		dest = ft_itoa_comp(dest, &nb, &i);
	dest[i] = nb % 10 + 48;
	dest[len] = '\0';
	return (dest);
}

int	countword2(char *s)
{
	int		d;
	int		i;

	i = 0;
	d = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			d++;
			i = ignormeta(s, i, s[i]);
		}
		if (s[i] != '\'' && s[i] != '\"' && s[i] != '\0')
		{
			d++;
			while (s[i] != '\'' && s[i] != '\"' && s[i] != '\0')
				i++;
		}
	}
	return (d);
}
