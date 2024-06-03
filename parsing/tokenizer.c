/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:18:31 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/01 16:38:02 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	tchevron(char *l)
{
	if (l[0] == '>' && l[1] == '\0')
		return (REDIROUT);
	if (l[0] == '<' && l[1] == '\0')
		return (REDIRIN);
	if (l[0] == '>' && l[1] == '>')
		return (APPND);
	return (HERED);
}

void	freecutword(char **c)
{
	int	i;

	i = 0;
	while (c[i] != NULL)
	{
		free(c[i]);
		i++;
	}
	free(c);
}

t_lex	*tokenizer(char **cl, int i)
{
	t_lex	*tmp;

	tmp = malloc(sizeof(t_lex) * (i + 1));
	tmp[i].mot = NULL;
	i--;
	while (i >= 0)
	{
		tmp[i].mot = ft_strdup(cl[i]);
		if (cl[i][0] == '|')
			tmp[i].tok = PIPE;
		else if (cl[i][0] == '<' || cl[i][0] == '>')
			tmp[i].tok = tchevron(cl[i]);
		else if (cl[i][0] == '\n')
			tmp[i].tok = NEWL;
		else
			tmp[i].tok = WORD;
		i--;
	}
	freecutword(cl);
	return (tmp);
}
