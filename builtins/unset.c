/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:59:32 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/03 18:59:42 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error_export(t_cmd **c, int i, int j)
{
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;

	s1 = ft_strjoin("Minishell: ", c[i]->cmd[0]);
	s2 = ft_strjoin(s1, ": ");
	s3 = ft_strjoin(s2, c[i]->cmd[j]);
	s4 = ft_strjoin(s3, " : identifiant non valable\n");
	write(2, s4, ft_strlen(s4));
	free(s1);
	free(s2);
	free(s3);
	free(s4);
	return (0);
}

void	delete_var(char *s, t_list *our_env)
{
	t_list	*temp;
	t_list	*tmp;
	int		len;

	len = ft_strlen(s);
	temp = our_env;
	while (temp && temp->next)
	{
		tmp = temp->next->next;
		if (ft_strncmp(temp->next->content, s, len) == 0
			&& temp->next->content[len] == '=')
		{
			free(temp->next->content);
			free(temp->next);
			temp->next = tmp;
		}
		temp = temp->next;
	}
}

int	is_in_env(char *s, t_list *our_env)
{
	t_list	*temp;
	int		len;

	len = ft_strlen(s);
	temp = our_env;
	while (temp)
	{
		if (ft_strncmp(temp->content, s, len) == 0)
		{
			if (temp->content[len] == '=')
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	incorrect_identifier(char *s)
{
	int	i;

	i = 0;
	if (!(('a' <= s[0] && s[0] <= 'z') || ('A' <= s[0] && s[0] <= 'Z')))
		return (1);
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	mini_unset(t_cmd **c, t_list *our_env, int i)
{
	int	j;
	int	k;

	k = 0;
	j = 1;
	while (c[i]->cmd[j])
	{
		if (is_in_env(c[i]->cmd[j], our_env) == 1)
			delete_var(c[i]->cmd[j], our_env);
		else if (incorrect_identifier(c[i]->cmd[j]) == 1)
		{
			print_error_identifiant(c, i);
			k = 1;
		}
		j++;
	}
	if (k == 1)
		return (1);
	return (0);
}
