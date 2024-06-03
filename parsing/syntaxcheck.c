/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 11:25:27 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/03 11:00:10 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntaxerror(t_lex *lex)
{
	int	i;

	i = 0;
	if (checkquote(lex) != 0)
		return (9);
	if (lex[0].tok == PIPE)
		return (PIPE);
	while (lex[i].tok != NEWL)
	{
		if (lex[i].tok > 2 && lex[i].tok < 8)
		{
			if (lex[i + 1].tok != 1)
				return (lex[i + 1].tok);
		}
		if (lex[i].tok == 2)
		{
			if (lex[i + 1].tok == 2)
				return (-1);
			if (lex[i + 1].tok == 8)
				return (8);
		}
		i++;
	}
	return (0);
}

int	closequote(char *l, char c, int *i)
{
	while (l[*i] != '\0')
	{
		if (l[*i] == c)
			return (0);
		*i = *i + 1;
	}
	return (1);
}

int	checkquote(t_lex *lex)
{
	int	i;
	int	d;

	i = 0;
	while (lex[i].tok != NEWL)
	{
		d = 0;
		if (lex[i].tok == 1)
		{
			while (lex[i].mot[d] != '\0')
			{
				if (lex[i].mot[d] == '\'' || lex[i].mot[d] == '\"')
				{
					d++;
					if (closequote(lex[i].mot, lex[i].mot[d - 1], &d) == 1)
						return (1);
				}
				d++;
			}
		}
		i++;
	}
	return (0);
}

void	psyntaxerror(int p)
{
	write(2, "Minishell : ", ft_strlen("Minishell : "));
	write(2, "syntax error ", ft_strlen("syntax error "));
	if (p == 8)
		write(2, "near tok « newline »", ft_strlen("near tok « newline »"));
	else if (p == 2)
		write(2, "near tok « | »", ft_strlen("near tok « | »"));
	else if (p == 4)
		write(2, "near tok « > »", ft_strlen("near tok « > »"));
	else if (p == 5)
		write(2, "near tok « > »", ft_strlen("near tok « > »"));
	else if (p == 6)
		write(2, "near tok « < »", ft_strlen("near tok « < »"));
	else if (p == 7)
		write(2, "near tok « << »", ft_strlen("near tok « << »"));
	else if (p == 9)
		write(2, "quotes not closed", ft_strlen("quotes not closed"));
	write(2, "\n", 1);
	g_exit_status = 2;
}
