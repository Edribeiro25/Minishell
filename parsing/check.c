/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:54:54 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/04 08:57:11 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen2(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	else
	{
		while (s[i])
			i++;
	}
	return (i);
}

int	ft_isalnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	ctword(char **l)
{
	int	i;

	i = 0;
	while (l[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	checkwd(char **l)
{
	int	i;

	i = 0;
	while (l[i] != NULL)
	{
		if (checkmot(l[i], 0, 0, 0) > 0)
			return (1);
		i++;
	}
	return (0);
}

void	checkcmd(t_cmd **tmp, t_list *l)
{
	int	i;

	i = 0;
	while (tmp[i] != NULL)
	{
		tmp[i]->rerror = 0;
		tmp[i]->command = ctword(tmp[i]->cmd);
		if (checkwd(tmp[i]->cmd) == 1)
			tmp[i]->cmd = changecmd1(tmp[i]->cmd, &tmp[i]->command, l);
		tmp[i]->command = ctword(tmp[i]->cmd);
		i++;
	}
}
