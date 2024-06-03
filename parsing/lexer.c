/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 12:00:46 by eribeiro          #+#    #+#             */
/*   Updated: 2022/03/31 13:03:23 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chevronsep(char *l, int i, int *ctw)
{
	int	c;

	c = *ctw;
	if (l[i + 1] == l[i])
		i = i + 2;
	else
		i++;
	c++;
	*ctw = c;
	return (i);
}

int	ignormeta(char *l, int i, char w)
{
	i++;
	while (l[i] != '\0' && l[i] != w)
	{
		i++;
	}
	if (l[i] == w)
		i++;
	return (i);
}

int	wordsep(char *l, int i, int *ctw)
{
	while (l[i] != '\0' && check_sep(l[i]) == 0)
	{
		if (l[i] == '\'' || l[i] == '\"')
			i = ignormeta(l, i, l[i]);
		if (l[i] != '\0' && check_sep(l[i]) == 0)
			i++;
	}
	*ctw = *ctw + 1;
	return (i);
}

int	spacesep(char *l, int i)
{
	while (l[i] != '\0' && l[i] == ' ')
		i++;
	return (i);
}

int	countword(char *l)
{
	int	i;
	int	ctw;

	ctw = 0;
	i = 0;
	while (l[i] && l[i] == ' ')
		i++;
	while (l[i] != '\0')
	{
		if (check_sep(l[i]) == 0 && l[i] != '\0' && check_sep(l[i]) == 0)
			i = wordsep(l, i, &ctw);
		if (check_sep(l[i]) == 1)
		{
			i++;
			ctw++;
		}
		if (check_sep(l[i]) == 2)
			i = spacesep(l, i);
		if (check_sep(l[i]) == 3)
			i = chevronsep(l, i, &ctw);
	}
	ctw++;
	return (ctw);
}
