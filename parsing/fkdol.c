/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fkdol.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:03:35 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/03 18:47:17 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lex	*token(char **l, int d, int n, t_list *env)
{
	t_lex	*lex;
	int		i;

	i = 0;
	lex = malloc(sizeof(t_lex) * n);
	if (!lex)
		return (NULL);
	while (l[i] != NULL)
	{
		d = checkmot(l[i], 0, 0, 0);
		lex[i].tok = d;
		if (d > 0)
			lex[i].mot = changeword(l[i], d, env);
		else
			lex[i].mot = ft_strdup(l[i]);
		i++;
	}
	return (lex);
}

void	freetok(t_lex *lex, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (lex[i].mot)
			free(lex[i].mot);
		i++;
	}
	free(lex);
}

int	rempm(char **tmp, t_lex *lex, int n, int i)
{
	int	c;

	c = 0;
	while (i < n)
	{
		if (lex[i].tok == 2)
		{
			if (ft_strlen(lex[i].mot) != 0)
				tmp[c++] = ft_strdup(lex[i].mot);
			else
				tmp[c] = NULL;
		}
		else
		{
			if (lex[i].mot)
				tmp[c] = ft_strdup(lex[i].mot);
			else
				tmp[c] = NULL;
			c++;
		}
		i++;
	}
	return (c);
}

int	countlex(t_lex *lex, int i, int n)
{
	int	c;

	c = 0;
	while (i < n)
	{
		if (lex[i].tok == 2)
		{
			if (ft_strlen(lex[i].mot) != 0)
				c++;
		}
		else
			c++;
		i++;
	}
	return (c);
}

char	**changecmd1(char **l, int *n, t_list *env)
{
	char	**tmp;
	t_lex	*lex;
	int		c;

	lex = token(l, 0, *n, env);
	c = countlex(lex, 0, *n);
	tmp = malloc(sizeof(char *) * (c + 1));
	if (!tmp)
		return (NULL);
	tmp[c] = NULL;
	c = rempm(tmp, lex, *n, 0);
	freetab(l, *n);
	freetok(lex, *n);
	*n = c ;
	return (tmp);
}
