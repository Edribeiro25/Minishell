/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:31:56 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 09:47:09 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	herectrld(char *l)
{
	write(2, "Minishell: warning: ", ft_strlen("Minishell: warning: "));
	write(2, "here-document ", ft_strlen("here-document "));
	write(2, "delimited", ft_strlen(" delimited"));
	write(2, "delimited by end-", ft_strlen("delimited by end-"));
	write(2, "of-file (wanted `", ft_strlen("of-file (wanted `"));
	write(2, l, ft_strlen(l));
	write(2, "')\n", ft_strlen("')\n"));
}

void	pushline(char *l, t_here h)
{
	char	*tmp;

	if (checkmot(l, 0, 0, 0) > 1)
	{
		tmp = dolhere(l, 0, h);
		if (tmp == NULL)
			write(h.pipe[1], "\n", 1);
		else
		{
			write(h.pipe[1], tmp, ft_strlen2(tmp));
			write(h.pipe[1], "\n", 1);
		}
		if (tmp)
			free(tmp);
		return ;
	}
	write(h.pipe[1], l, ft_strlen2(l));
	write(h.pipe[1], "\n", 1);
}

void	here(char *t, int i, t_here h)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			herectrld(t);
			break ;
		}
		else if (ft_strcmp(t, line) == 0)
		{
			free(line);
			break ;
		}
		else if (line != NULL && i == 0)
		{
			pushline(line, h);
			free(line);
		}
		else
			free(line);
	}
}

void	freeh(t_here h)
{
	int		i;

	i = 0;
	free(h.pipe);
	free_env(h.env);
	while (h.c[i] != NULL)
	{
		free(h.c[i]);
		i++;
	}
	freecmdexe(h.he.c);
	freelex(h.he.lex);
	free(h.c);
}

void	heredone(t_here h)
{	
	int		i;
	int		end;
	int		fin;

	fin = 1;
	i = 0;
	end = ctword(h.c);
	g_exit_status = -1;
	while (i < end && g_exit_status != 130)
	{
		if (i == end - 1)
			fin = 0;
		if (i < end)
		{
			here(h.c[i], fin, h);
		}
		i++;
	}
	freeh(h);
	exit (0);
}
