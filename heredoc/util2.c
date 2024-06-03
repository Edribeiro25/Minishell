/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 11:52:21 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 09:45:41 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	heredocend(t_cmd *c, t_here h, pid_t pid)
{
	if (pid == 33280)
	{
		g_exit_status = 130;
		close(h.pipe[1]);
		close(h.pipe[0]);
		freetab(h.c, ctword(h.c));
		free(h.pipe);
		return (1);
	}
	else
	{
		g_exit_status = h.errorcode;
		close(h.pipe[1]);
		c->fdin = h.pipe[0];
		freetab(h.c, ctword(h.c));
		free(h.pipe);
		return (0);
	}
}

int	gohere(t_doc he, t_cmd *c, t_list *e, int *i)
{
	t_here	h;
	int		d;
	pid_t	doco;
	int		docostat;

	d = *i;
	docostat = 0;
	h.env = e;
	h.he = he;
	h.c = recupehere(he.lex, &d, 0);
	h.errorcode = g_exit_status;
	g_exit_status = -3;
	h.pipe = malloc(sizeof(int) * 2);
	if (!h.pipe)
		write(2, "MALLOC PIPE FAILED\n", ft_strlen("MALLOC PIPE FAILED\n"));
	pipe(h.pipe);
	doco = fork();
	if (doco == 0)
		heredone(h);
	else
		waitpid(doco, &docostat, 0);
	*i = d;
	d = heredocend(c, h, docostat);
	return (d);
}

int	testlast(int i, t_lex *l)
{
	while (i >= 0 && l[i].tok != HERED)
	{
		if (l[i].tok == REDIRIN)
			return (0);
		i--;
	}
	return (1);
}

int	heredoc(t_lex *l, t_cmd **c, t_list *e, int i)
{
	int		j;
	int		v;
	t_doc	he;

	v = 0;
	j = 0;
	he.c = c;
	he.lex = l;
	while (l[i].tok != NEWL && v == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		if (l[i].tok == PIPE)
		{
			i++;
			j++;
		}
		if (l[i].tok == HERED && v == 0)
		{
			v = gohere(he, c[j], e, &i);
			c[j]->here = testlast(i, l);
		}
		if (l[i].tok != NEWL && l[i].tok != PIPE)
			i++;
	}
	return (v);
}
