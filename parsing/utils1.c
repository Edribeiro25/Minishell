/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:41:27 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 09:46:17 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parsing(t_lex *l, t_cmd **c, t_list *e)
{
	int	d;

	d = 0;
	setsig(0);
	d = heredoc(l, c, e, 0);
	if (d == 0)
		redir(l, c, e, 0);
	return (d);
}

int	onlyspace(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

void	listfree(void *mem)
{
	if (mem)
		free(mem);
}
