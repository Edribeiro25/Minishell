/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:59:08 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 17:28:49 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	erreurtp(t_cmd **c)
{
	if (c[0]->pipe == 0)
		write(2, "exit\nMinishell: exit: trop d'arguments\n", 39);
	else
		write(2, "Minishell: exit: trop d'arguments\n", 34);
	return (1);
}

int	exitvalue(t_cmd **c, t_list *our_env, int i, char *s)
{
	long long	nb;

	nb = ft_atoi_long(s);
	free(s);
	if (i == c[0]->pipe)
	{
		if (c[0]->pipe == 0)
			write(1, "exit\n", 5);
		freecmdexe(c);
		free_env(our_env);
		exit(nb % 256);
	}
	return (0);
}

int	mini_exit_3(char *s, t_cmd **c, t_list *our_env, int i)
{
	int	d;

	d = -1;
	if (ft_strlen(s) == 19)
			d = ft_strcmp(s, "9223372036854775807");
	if (d > 0)
	{
		free(s);
		return (erreurnum(c, our_env, i));
	}
	return (exitvalue(c, our_env, i, s));
}

int	mini_exit_2(char *s, t_cmd **c, t_list *our_env, int i)
{
	int	d;

	d = -1;
	if (s[0] == '-')
	{
		if (ft_strlen(s) == 20)
			d = ft_strcmp(s, "-9223372036854775808");
		if (d > 0)
		{
			free(s);
			return (erreurnum(c, our_env, i));
		}
		if (d == 0)
		{
			free(s);
			exitsimple(c, our_env, i);
		}
		return (exitvalue(c, our_env, i, s));
	}
	else
		return (mini_exit_3(s, c, our_env, i));
	return (0);
}

int	mini_exit(t_cmd **c, t_list *our_env, int i)
{
	char	*str;

	if (c[i]->command == 1)
		return (exitsimple(c, our_env, i));
	if (checknb(c[i]->cmd[1]) == 1)
		return (erreurnum(c, our_env, i));
	if (c[i]->command > 2)
		return (erreurtp(c));
	str = delete_spaces(c[i]->cmd[1], 0);
	if (ft_strlen(str) > 20)
	{
		free(str);
		return (erreurnum(c, our_env, i));
	}
	mini_exit_2(str, c, our_env, i);
	return (0);
}
