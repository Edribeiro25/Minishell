/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:59:38 by aazra             #+#    #+#             */
/*   Updated: 2022/04/04 21:44:36 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(t_cmd **c, int i, int k)
{
	int	j;

	j = 2;
	while (c[i]->cmd[k][j] == 'n')
		j++;
	if (c[i]->cmd[k][j] == '\0')
		return (0);
	else
		return (1);
}

int	mini_echo_one(t_cmd **c, int i)
{
	int	n;
	int	k;

	n = 0;
	k = 1;
	while (c[i]->cmd[k] && ft_strncmp(c[i]->cmd[k], "-n", 2) == 0
		&& check_n(c, i, k) == 0)
		k++;
	if (k > 1)
		n = 1;
	while (c[i]->cmd[k] != NULL)
	{
		if (write(c[i]->fdout, c[i]->cmd[k], ft_strlen(c[i]->cmd[k])) == -1)
		{
			print_error2(c, c[i]->cmd[0]);
			return (1);
		}
		if (c[i]->cmd[k + 1] != NULL)
			write(c[i]->fdout, " ", 1);
		k++;
	}
	if (n == 0)
		write(c[i]->fdout, "\n", 1);
	return (0);
}

int	mini_echo(t_cmd **c, int i)
{
	int	n;
	int	k;

	n = 0;
	k = 1;
	while (c[i]->cmd[k] && ft_strncmp(c[i]->cmd[k], "-n", 2) == 0
		&& check_n(c, i, k) == 0)
		k++;
	if (k > 1)
		n = 1;
	while (c[i]->cmd[k] != NULL)
	{
		if (write(1, c[i]->cmd[k], ft_strlen(c[i]->cmd[k])) == -1)
		{
			print_error2(c, c[i]->cmd[0]);
			return (1);
		}
		if (c[i]->cmd[k + 1] != NULL)
			write(1, " ", 1);
		k++;
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}

int	is_builtin(t_cmd **c, int i)
{
	if (ft_strcmp(c[i]->cmd[0], "echo") == 0
		|| ft_strcmp(c[i]->cmd[0], "cd") == 0
		|| ft_strcmp(c[i]->cmd[0], "pwd") == 0
		|| ft_strcmp(c[i]->cmd[0], "export") == 0
		|| ft_strcmp(c[i]->cmd[0], "unset") == 0
		|| ft_strcmp(c[i]->cmd[0], "env") == 0
		|| ft_strcmp(c[i]->cmd[0], "exit") == 0)
		return (1);
	return (0);
}

int	use_builtin(t_cmd **c, t_list *our_env, int i)
{
	if (c[i]->fdin == -1 || c[i]->fdout == -1)
		return (1);
	if (ft_strcmp(c[i]->cmd[0], "pwd") == 0 && c[0]->pipe > 0)
		return (mini_pwd());
	if (ft_strcmp(c[i]->cmd[0], "pwd") == 0 && c[0]->pipe == 0)
		return (mini_pwd_one(c, i));
	if (ft_strcmp(c[i]->cmd[0], "echo") == 0 && c[0]->pipe > 0)
		return (mini_echo(c, i));
	if (ft_strcmp(c[i]->cmd[0], "echo") == 0 && c[0]->pipe == 0)
		return (mini_echo_one(c, i));
	if (ft_strcmp(c[i]->cmd[0], "env") == 0 && c[0]->pipe > 0)
		return (mini_env(our_env));
	if (ft_strcmp(c[i]->cmd[0], "env") == 0 && c[0]->pipe == 0)
		return (mini_env_one(c, our_env, i));
	if (ft_strcmp(c[i]->cmd[0], "export") == 0)
		return (mini_export(c, &our_env, i));
	if (ft_strcmp(c[i]->cmd[0], "exit") == 0)
		return (mini_exit(c, our_env, i));
	if (ft_strcmp(c[i]->cmd[0], "cd") == 0)
		return (mini_cd(c[i], &our_env, c[i]->command));
	if (ft_strcmp(c[i]->cmd[0], "unset") == 0)
		return (mini_unset(c, our_env, i));
	return (0);
}
