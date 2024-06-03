/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:57:35 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/03 22:42:12 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_export(t_cmd **c, int i, int j)
{
	int	k;

	k = 0;
	while (c[i]->cmd[j][k])
	{
		if (c[i]->cmd[j][k] == '=')
			return (1);
		k++;
	}
	return (0);
}

int	var_exists(t_cmd **c, t_list **our_env, int j)
{
	int		len;
	t_list	*tmp;

	len = 0;
	tmp = *our_env;
	while (c[0]->cmd[j][len] != '=')
		len++;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, c[0]->cmd[j], len) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	mini_export_3(t_cmd **c, int i, int j, int *k)
{
	while (c[i]->cmd[j])
	{
		if (!(('a' <= c[i]->cmd[j][0] && c[i]->cmd[j][0] <= 'z')
			|| ('A' <= c[i]->cmd[j][0] && c[i]->cmd[j][0] <= 'Z'))
			|| is_alnum(c[i]->cmd[j]) == 0)
		{
			print_error_export(c, i, j);
			*k = 1;
		}
		j++;
	}
	if (*k == 1)
		return (1);
	return (0);
}

void	mini_export_2(t_cmd **c, int j, int *k, t_list **our_env)
{
	char	*s;
	t_list	*new;

	if (!(('a' <= c[0]->cmd[j][0] && c[0]->cmd[j][0] <= 'z')
		|| ('A' <= c[0]->cmd[j][0] && c[0]->cmd[j][0] <= 'Z'))
		|| is_alnum(c[0]->cmd[j]) == 0)
	{
		printf("Minishell: export: %s : identifiant non valable\n", \
			c[0]->cmd[j]);
		*k = 1;
	}
	else if (arg_export(c, 0, j) == 1 && var_exists(c, our_env, j) == 0)
	{
		s = (char *)malloc(sizeof(char) * (ft_strlen(c[0]->cmd[j]) + 1));
		if (!s)
			global_error("Malloc failed\n", 1);
		ft_strlcpy(s, c[0]->cmd[j], ft_strlen(c[0]->cmd[j]) + 1);
		new = ft_lstnew(s);
		if (!new)
			global_error("Malloc failed\n", 1);
		ft_lstadd_back(our_env, new);
	}
	else if (arg_export(c, 0, j) == 1 && var_exists(c, our_env, j) == 1)
		change_var_content(c, our_env, j);
}

int	mini_export(t_cmd **c, t_list **our_env, int i)
{
	int	j;
	int	k;

	j = 1;
	k = 0;
	if (!c[i]->cmd[1])
	{
		return (export_alone(*our_env));
	}
	else if (i == 0 && c[0]->pipe == 0 && c[i]->cmd[1])
	{
		while (c[0]->cmd[j])
		{
			mini_export_2(c, j, &k, our_env);
			j++;
		}
		if (k == 1)
			return (1);
	}
	else if (c[0]->pipe > 0 && c[i]->cmd[1])
	{
		return (mini_export_3(c, i, j, &k));
	}
	return (0);
}
