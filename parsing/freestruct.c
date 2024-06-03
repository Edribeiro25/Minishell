/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestruct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 11:20:57 by eribeiro          #+#    #+#             */
/*   Updated: 2022/03/31 13:12:39 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	freelex(t_lex *lex)
{
	int	i;

	i = 0;
	while (lex[i].tok != NEWL)
	{
		free(lex[i].mot);
		i++;
	}
	free(lex[i].mot);
	free(lex);
}

void	freecmdexe(t_cmd **c)
{
	int	i;
	int	j;

	i = 0;
	while (c[i] != NULL)
	{
		if (c[i]->command >= 0)
		{
			j = 0;
			while (j < c[i]->command)
			{
				free(c[i]->cmd[j]);
				j++;
			}
			free(c[i]->cmd[j]);
			free(c[i]->cmd);
		}
		free(c[i]);
		i++;
	}
	free(c[i]);
	free(c);
}

void	freetab(char **l, int i)
{
	int	d;

	d = 0;
	while (d < i)
	{
		free(l[d]);
		d++;
	}
	if (l[d])
		free(l[d]);
	free(l);
}
