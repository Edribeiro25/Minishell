/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutcmd1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 11:15:56 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/01 16:36:27 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countcmd1(t_lex *lex)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (lex[i].tok != NEWL)
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

char	**takecmd1(t_lex *lex, int z)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = malloc(sizeof(char *) * (z + 1));
	tmp[z] = NULL;
	z = 0;
	while (lex[i].tok != NEWL)
	{
		if (lex[i].tok == WORD)
		{
			tmp[z] = ft_strdup(lex[i].mot);
			z++;
		}
		if (lex[i].tok >= REDIROUT && lex[i].tok <= HERED)
			i++;
		if (lex[i].tok != NEWL)
			i++;
	}
	return (tmp);
}

t_cmd	**cutcmd1(t_lex *lex, int i)
{
	t_cmd	**tmp;

	tmp = malloc(sizeof(t_cmd *) * 2);
	if (!tmp)
		return (NULL);
	tmp[1] = NULL;
	tmp[0] = malloc(sizeof(t_cmd) * 1);
	if (!tmp[0])
		return (NULL);
	tmp[0]->exitstat = 0;
	tmp[0]->pipe = 0;
	tmp[0]->fdin = 0;
	tmp[0]->here = 0;
	tmp[0]->fdout = 1;
	if (i != 0)
		tmp[0]->command = 1;
	else
		tmp[0]->command = 0;
	tmp[0]->cmd = takecmd1(lex, i);
	return (tmp);
}

t_cmd	**createcmd(t_lex *lex, t_list *l)
{
	int		i;
	int		c;
	t_cmd	**tmp;

	c = 1;
	i = 0;
	while (lex[i].tok != NEWL)
	{
		if (lex[i].tok == PIPE)
			c++;
		i++;
	}
	if (c == 1)
	{
		i = countcmd1(lex);
		tmp = cutcmd1(lex, i);
	}
	if (c > 1)
		tmp = cutcmd2(lex, c, 0);
	i = 0;
	checkcmd(tmp, l);
	return (tmp);
}
