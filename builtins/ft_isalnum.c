/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:02:24 by aazra             #+#    #+#             */
/*   Updated: 2022/04/05 12:30:20 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	triple_free(char **s, t_cmd **c, t_list *our_env)
{
	free_strings(s);
	free_env(our_env);
	freecmdexe(c);
}

void	mini_exit_final(t_cmd **c, t_list *our_env, int i)
{
	free_env(our_env);
	freecmdexe(c);
	exit(i);
}

int	is_alnum(char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (!((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z')
				|| (s[i] >= 'A' && s[i] <= 'Z')))
			return (0);
		i++;
	}
	return (1);
}

void	cond_pipe(t_cmd **c, int i)
{
	if (c[i]->fdin > 2)
	{
		dup2(c[i]->fdin, STDIN_FILENO);
		close(c[i]->fdin);
	}
}
