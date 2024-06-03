/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:16:21 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/01 19:10:46 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cutword2bis(int *i, char *s)
{
	int		d;
	int		r;
	char	*tmp;

	d = *i;
	*i = ignormeta(s, *i, s[*i]);
	tmp = malloc(sizeof(char) * (*i - d + 1));
	if (!tmp)
		return (NULL);
	tmp[*i - d] = '\0';
	r = 0;
	while (d < *i)
	{
		tmp[r] = s[d];
		r++;
		d++;
	}
	return (tmp);
}

char	*cutword2tre(int *i, char *s)
{
	int		d;
	int		r;
	char	*tmp;

	d = *i;
	while (s[*i] != '\'' && s[*i] != '\"' && s[*i] != '\0')
		*i = *i + 1;
	tmp = malloc(sizeof(char) * (*i - d + 1));
	if (!tmp)
		return (NULL);
	tmp[*i - d] = '\0';
	r = 0;
	while (d < *i)
	{
		tmp[r] = s[d];
		r++;
		d++;
	}
	return (tmp);
}

int	cutword2(char *s, char **cl, int p)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			cl[p] = cutword2bis(&i, s);
			p++;
		}
		if (s[i] != '\'' && s[i] != '\"' && s[i] != '\0')
		{
			cl[p] = cutword2tre(&i, s);
			p++;
		}
	}
	return (0);
}
