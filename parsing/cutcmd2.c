/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutcmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 11:22:19 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/01 19:18:52 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**takecmd2(t_lex *lex, int z, int *l, int c)
{
	char	**tmp;
	int		i;

	i = *l;
	tmp = malloc(sizeof(char *) * (z + 1));
	if (!tmp)
		return (NULL);
	tmp[z] = NULL;
	while (lex[i].tok != NEWL && lex[i].tok != PIPE)
	{
		if (lex[i].tok == WORD)
		{
			tmp[c] = ft_strdup(lex[i].mot);
			c++;
		}
		if (lex[i].tok >= REDIROUT && lex[i].tok <= HERED)
			i++;
		if (lex[i].tok != NEWL)
			i++;
	}
	if (lex[i].tok == PIPE)
		i++;
	*l = i;
	return (tmp);
}

int	countcmd2(t_lex *lex, int i)
{
	int	c;

	c = 0;
	while (lex[i].tok != NEWL && lex[i].tok != PIPE)
	{
		if (lex[i].tok == WORD)
			c++;
		if (lex[i].tok >= REDIROUT && lex[i].tok <= HERED)
			i++;
		if (lex[i].tok != NEWL)
			i++;
	}
	return (c);
}

t_cmd	*tmpset(int i)
{
	t_cmd	*tmp;

	tmp = malloc(sizeof(t_cmd) * 1);
	if (!tmp)
		return (NULL);
	tmp->fdin = 0;
	tmp->fdout = 1;
	tmp->here = 0;
	tmp->exitstat = 0 ;
	tmp->pipe = i - 1;
	return (tmp);
}

t_cmd	**cutcmd2(t_lex *lex, int i, int r)
{
	t_cmd	**tmp;
	int		d;
	int		c;

	tmp = malloc(sizeof(t_cmd *) * (i + 1));
	if (!tmp)
		return (NULL);
	tmp[i] = NULL;
	d = 0;
	while (d < i)
	{
		c = 0;
		tmp[d] = tmpset(i);
		c = countcmd2(lex, r);
		if (c == 0)
			tmp[d]->command = 0;
		else
			tmp[d]->command = 1;
		tmp[d]->cmd = takecmd2(lex, c, &r, 0);
		d++;
	}
	return (tmp);
}
