/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newdol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:10:05 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 12:31:43 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rejoin2(char **l, char *tmp, int i)
{
	int		r;
	int		h;
	int		c;

	h = 0;
	c = 0;
	while (c < i)
	{
		if (l[c] != NULL)
		{
			r = 0;
			while (l[c][r] != '\0')
			{
				tmp[h] = l[c][r];
				r++;
				h++;
			}
		}
		c++;
	}
	tmp[h] = '\0';
}

char	*rejoins(char **l, int i)
{
	char	*tmp;
	int		c;
	int		r;

	c = 0;
	r = 0;
	while (c < i)
	{
		r += ft_strlen2(l[c]);
		c++;
	}
	tmp = malloc(sizeof(char) * (r + 1));
	if (!tmp)
		return (NULL);
	rejoin2(l, tmp, i);
	return (tmp);
}

int	countq(char *s, int i)
{
	int		quote;

	quote = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			quote = 1;
			break ;
		}
		i++;
	}
	return (quote);
}

int	checkmot(char *s, int i, int doll, int quote)
{
	quote = countq(s, 0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			i = ignormeta(s, i, s[i]);
		if (s[i] == '$' && isdol(s[i + 1]))
			doll = 2;
		if (s[i] == '\"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\"')
			{
				if (s[i] == '$')
					doll = 2;
				i++;
			}
			i++;
		}
		if (s[i] != '\0' && s[i] != '\'')
			i++;
	}
	return (doll + quote);
}

char	*nondol(char *s, int *i)
{
	char	*tmp;
	int		r;
	int		d;

	r = 0;
	d = *i;
	while (s[d] != '\0' && s[d] != '$')
	{
		r++;
		d++;
	}
	tmp = malloc(sizeof(char) * (r + 1));
	if (!tmp)
		return (NULL);
	tmp[r] = '\0';
	r = 0;
	while (*i < d)
	{
		tmp[r] = s[*i];
		r++;
		*i = *i + 1;
	}
	return (tmp);
}
