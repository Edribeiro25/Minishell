/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:45:18 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/04 09:15:26 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	change_var_cd(char *c, t_list **our_env)
{
	t_list	*tmp;
	int		len;

	len = 0;
	tmp = *our_env;
	while (c[len] != '=')
		len++;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, c, len) == 0)
		{
			free(tmp->content);
			tmp->content = (char *)malloc(sizeof(char) * \
					(ft_strlen(c) + 1));
			if (!tmp->content)
				global_error("Malloc failed\n", 1);
			len = 0;
			while (c[len++])
				tmp->content[len - 1] = c[len - 1];
			tmp->content[len - 1] = '\0';
		}
		tmp = tmp->next;
	}
}

void	changeset(t_list **env, char *l)
{
	char	*l1;
	char	*l2;

	l2 = NULL;
	if (is_in_env("OLDPWD",*env) == 1)
	{
		l1 = ft_strjoin("OLDPWD=", l);
		change_var_cd(l1, env);
		free(l1);
	}
	if (is_in_env("PWD", *env) == 1)
	{
		l2 = getcwd(NULL, 0);
		l1 = ft_strjoin("PWD=", l2);
		change_var_cd(l1, env);
		free(l1);
		free(l2);
	}
}

int	changehome(t_list **env)
{
	char	*l;
	char	*lo;

	lo = getcwd(NULL, 0);
	if (!lo)
		write(2, "error_pwd\n", 10);
	if (is_in_env("HOME",*env) == 0)
	{
		write(2, "Minishell: cd: << HOME >> is not set\n", 38);
		return (1);
	}
	else
		l = get_var("HOME=", *env);
	if (chdir(l) != 0)
	{
		cder(l);
		free(l);
		return (1);
	}
	if (l)
		free(l);
	changeset(env, lo);
	return (0);
}

int	changedir(t_list **env, char *s)
{
	char	loc[512];

	if (ft_strlen(s) == 0)
		return (0);
	if (getcwd(loc, sizeof(loc)) == NULL)
		write(2, "error_pwd\n", 10);
	if (chdir(s) != 0)
	{
		cder(s);
		return (1);
	}
	else
		changeset(env, loc);
	return (0);
}

int	mini_cd(t_cmd *c, t_list **env, int i)
{
	if (i > 2)
	{
		write(2, "Minishell : cd: too many argument\n", 35);
		return (1);
	}
	if (!c->cmd[1] && c->command == 1)
		return (changehome(env));
	if (ft_strcmp(c->cmd[1], "--") == 0)
		return (changehome(env));
	else
		return (changedir(env, c->cmd[1]));
	return (0);
}
