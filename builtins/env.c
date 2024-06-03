/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:01:00 by aazra             #+#    #+#             */
/*   Updated: 2022/04/05 11:28:48 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_list *our_env)
{
	ft_lstclear(&our_env, listfree);
	rl_clear_history();
}

void	get_env_2(t_list **our_env, char **env)
{
	t_list	*new;
	char	*s;

	s = (char *)malloc(sizeof(char) * (ft_strlen(*env) + 1));
	if (!s)
		global_error("Malloc failed\n", 1);
	ft_strlcpy(s, *env, ft_strlen(*env) + 1);
	new = ft_lstnew(s);
	if (!new)
		global_error("Malloc failed\n", 1);
	if (!*our_env)
		*our_env = new;
	else
		ft_lstadd_back(our_env, new);
}

void	get_env(t_list **our_env, char **env)
{
	while (*env)
	{
		get_env_2(our_env, env);
		env++;
	}
}

int	mini_env(t_list *our_env)
{
	t_list	*temp;

	temp = our_env;
	while (temp)
	{
		write(1, temp->content, ft_strlen(temp->content));
		write(1, "\n", 1);
		temp = temp->next;
	}
	return (0);
}

int	mini_env_one(t_cmd **c, t_list *our_env, int i)
{
	t_list	*temp;

	temp = our_env;
	while (temp)
	{
		write(c[i]->fdout, temp->content, ft_strlen(temp->content));
		write(c[i]->fdout, "\n", 1);
		temp = temp->next;
	}
	return (0);
}
