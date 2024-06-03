/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:42:58 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/02 10:28:54 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	chevroncut(char *l, int i, char **tmp, int *m)
{
	char	*t;

	if (l[i + 1] == l[i])
	{
		t = malloc(sizeof(char) * 3);
		if (!t)
			return (0);
		t[0] = l[i];
		t[1] = l[i];
		t[2] = '\0';
		i = i + 2;
	}
	else
	{
		t = malloc(sizeof(char) * 2);
		if (!t)
			return (0);
		t[0] = l[i];
		t[1] = '\0';
		i++;
	}
	*m = *m + 1;
	*tmp = t;
	return (i);
}

int	cutw(char *l, int i, char **sp, int *m)
{
	int		r;
	int		y;
	char	*tmp;

	y = i;
	r = 0;
	i = wordsep(l, i, &r);
	tmp = malloc(sizeof(char) * (i - y + 1));
	if (!tmp)
		return (0);
	tmp[i - y] = '\0';
	r = 0;
	while (y < i)
	{
		tmp[r] = l[y];
		r++;
		y++;
	}
	*m = *m + 1;
	*sp = tmp;
	return (i);
}

int	pipecut(int i, char **sp, int *d)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * 2);
	tmp[0] = '|';
	tmp[1] = '\0';
	i++;
	*sp = tmp;
	*d = *d + 1;
	return (i);
}

char	*newtok(void)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * 2);
	if (!tmp)
		return (NULL);
	tmp[0] = '\n';
	tmp[1] = '\0';
	return (tmp);
}

char	**cutword(char *l, int d)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (d + 1));
	if (!tmp)
		return (NULL);
	tmp[d] = NULL;
	d = 0;
	i = 0;
	while (l[i] && l[i] == ' ')
		i++;
	while (l[i] != '\0')
	{
		if ((check_sep(l[i]) == 0) && l[i] != '\0')
			i = cutw(l, i, &tmp[d], &d);
		if (check_sep(l[i]) == 1)
			i = pipecut(i, &tmp[d], &d);
		if (check_sep(l[i]) == 2)
			i = spacesep(l, i);
		if (check_sep(l[i]) == 3)
			i = chevroncut(l, i, &tmp[d], &d);
	}
	tmp[d] = newtok();
	return (tmp);
}
