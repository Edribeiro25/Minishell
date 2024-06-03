/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:05:36 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/02 18:50:53 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countch(char *s, int i, int c)
{
	char	sk;

	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			sk = s[i];
			i++;
			while (s[i] != sk)
			{
				c++;
				i++;
			}
			i++;
		}
		if (s[i] != '\'' && s[i] != '\"' && s[i] != '\0')
		{
			c++;
			i++;
		}
	}
	return (c);
}

void	rempmyword(char *s, int i, int c, char *tmp)
{
	char	sk;

	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			sk = s[i];
			i++;
			while (s[i] != sk)
			{
				tmp[c] = s[i];
				c++;
				i++;
			}
			i++;
		}
		if (s[i] != '\'' && s[i] != '\"' && s[i] != '\0')
		{
			tmp[c] = s[i];
			c++;
			i++;
		}
	}
}

char	*supprquote(char *s, int f)
{
	char	*tmp;
	int		c;

	c = countch(s, 0, 0);
	tmp = malloc(sizeof(char) * (c + 1));
	if (!tmp)
		return (NULL);
	tmp[c] = '\0';
	c = 0;
	rempmyword(s, 0, 0, tmp);
	if (f == 1)
		free(s);
	return (tmp);
}

int	checkchar(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
