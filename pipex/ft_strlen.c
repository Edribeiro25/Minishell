/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:10:40 by aazra             #+#    #+#             */
/*   Updated: 2022/04/05 17:39:43 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	launch_cmd2_3(t_cmd **c, t_list *our_env)
{
	int	i;

	i = 0;
	if (is_builtin(c, 1) == 1)
		i = use_builtin(c, our_env, 1);
	freecmdexe(c);
	free_env(our_env);
	return (i);
}
