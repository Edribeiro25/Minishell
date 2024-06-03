/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dol2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:20:32 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/04 08:21:12 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replaceword(char **cl, int i, t_list *env)
{
	char	*tmp;

	while (cl[i] != NULL)
	{
		if (cl[i][0] == '\'')
			cl[i] = supprquote(cl[i], 1);
		else
		{
			if (cl[i][0] == '\"')
				cl[i] = supprquote(cl[i], 1);
			if (checkdoll(cl[i]) == 1)
			{
				tmp = doluni(cl[i], 0, env);
				free(cl[i]);
				cl[i] = tmp;
			}
		}
		i++;
	}
	return (0);
}

char	*quotdoll(char *l, int c, t_list *env)
{
	char	**cl;
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	c = countword2(l);
	cl = malloc(sizeof(char *) * (c + 1));
	if (!cl)
		return (NULL);
	cl[c] = NULL;
	cutword2(l, cl, 0);
	replaceword(cl, 0, env);
	tmp = rejoins(cl, c);
	i++;
	freetab(cl, c);
	return (tmp);
}

char	*changeword(char *l, int c, t_list *env)
{
	char	*tmp;

	if (c == 1)
		tmp = supprquote(l, 0);
	if (c == 2)
		tmp = doluni(l, 0, env);
	if (c == 3)
		tmp = quotdoll(l, 0, env);
	return (tmp);
}

void	changecmd(char **l, t_list *env)
{
	int	i;
	int	c;

	i = 0;
	while (l[i] != NULL)
	{
		c = 0;
		c = checkmot(l[i], 0, 0, 0);
		if (c > 0)
			l[i] = changeword(l[i], c, env);
		i++;
	}
}
