/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llmin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 08:35:29 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 17:33:05 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*delete_spaces(char *s, int i)
{
	int		j;
	char	*str;

	while (s[i] && s[i] == ' ')
		i++;
	j = 0;
	while (s[i] && s[i] != ' ')
	{
		j++;
		i++;
	}
	str = (char *)malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i] && s[i] != ' ')
	{
		str[j] = s[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	nb(char s)
{
	if (s >= '0' && s <= '9')
		return (0);
	return (1);
}

int	checknb2(char *s, int i)
{
	while (s[i] != '\0')
	{
		if (nb(s[i]) == 0)
		{
			while (s[i] != '\0' && nb(s[i]) == 0)
				i++;
			while (s[i] != '\0' && s[i] == ' ')
				i++;
			if (s[i] != '\0')
				return (1);
		}
		else
			return (1);
		if (s[i] != '\0')
			i++;
	}
	return (0);
}

int	checknb(char *s)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\0')
		return (1);
	if ((s[i] == '-' || s[i] == '+') && nb(s[i + 1]) == 1)
		return (1);
	else if (s[i] == '-' || s[i] == '+')
		i++;
	r = checknb2(s, i);
	return (r);
}

int	exitsimple(t_cmd **c, t_list *our_env, int i)
{
	if (i == c[0]->pipe)
	{
		freecmdexe(c);
		free_env(our_env);
		exit(0);
	}
	else
		return (0);
}
