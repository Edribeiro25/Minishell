/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:06:33 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 09:44:09 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	redir(t_lex *l, t_cmd **c, t_list *e, int i)
{
	int	r;
	int	j;

	r = 0;
	j = 0;
	while (l[i].tok != NEWL)
	{
		if (l[i].tok == PIPE)
		{
			j++;
			r = 0;
		}
		if (l[i].tok == REDIRIN || l[i].tok == REDIROUT || l[i].tok == APPND)
		{
			i++;
			redirinter(l, c[j], e, i);
			if ((c[j]->fdout < 0 || c[j]->fdin < 0) && r != 1)
				r = 1;
		}
		if (l[i].tok != NEWL)
			i++;
	}
	return (r);
}

void	redirinter2(t_lex *l, t_cmd *c, t_list *e, int i)
{
	int		d;

	d = 0;
	if (c->here == 0)
	{
		if (c->fdin > 2)
			close (c->fdin);
		if (c->fdin != -1 && c->fdout != -1)
			c->fdin = redircheck(&c->rerror, l[i - 1].tok, l[i].mot, e);
		else
			c->fdin = -1;
	}
	else
	{
		if (c->fdin != -1 && c->fdout != -1)
			d = redircheck(&c->rerror, l[i - 1].tok, l[i].mot, e);
		if (d == -1)
			c->fdin = -1;
	}
}

void	redirinter(t_lex *l, t_cmd *c, t_list *e, int i)
{
	if (l[i - 1].tok == REDIROUT || l[i - 1].tok == APPND)
	{
		if (c->fdout > 2)
			close (c->fdout);
		if (c->fdin != -1 && c->fdout != -1)
			c->fdout = redircheck(&c->rerror, l[i - 1].tok, l[i].mot, e);
		else
			c->fdin = -1;
	}
	if (l[i - 1].tok == REDIRIN)
		redirinter2(l, c, e, i);
}

char	**recupehere(t_lex *l, int *i, int co)
{
	char	**here;
	int		d;

	d = *i;
	while (l[*i].tok != NEWL && l[*i].tok != PIPE)
	{
		if (l[*i].tok == HERED)
			co++;
		*i = *i + 1;
	}
	here = malloc(sizeof(char *) * (co + 1));
	here[co] = NULL;
	co = 0;
	while (l[d].tok != NEWL && l[d].tok != PIPE)
	{
		if (l[d].tok == HERED)
		{
			d++;
			here[co] = ft_strdup(l[d].mot);
			here[co] = supprquote(here[co], 1);
			co++;
		}
		d++;
	}
	return (here);
}
