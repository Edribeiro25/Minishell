/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:59:38 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/03 18:59:39 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_var_content(t_cmd **c, t_list **our_env, int j)
{
	t_list	*tmp;
	int		len;

	len = 0;
	tmp = *our_env;
	while (c[0]->cmd[j][len] != '=')
		len++;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, c[0]->cmd[j], len) == 0)
		{
			free(tmp->content);
			tmp->content = (char *)malloc(sizeof(char) * \
				(ft_strlen(c[0]->cmd[j]) + 1));
			if (!tmp->content)
				global_error("Malloc failed\n", 1);
			len = 0;
			while (c[0]->cmd[j][len++])
				tmp->content[len - 1] = c[0]->cmd[j][len - 1];
			tmp->content[len - 1] = '\0';
		}
		tmp = tmp->next;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-2000);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	export_alone2(int i, char **s)
{
	char	*tmp;

	while (s[i])
	{
		tmp = ft_strjoin("declare -x ", s[i]);
		if (!tmp)
			global_error("Malloc failed\n", 1);
		free(s[i]);
		s[i] = tmp;
		i++;
	}
	i = 0;
	while (s[i])
	{
		write(1, s[i], ft_strlen(s[i]));
		write(1, "\n", 1);
		i++;
	}
}

int	export_alone(t_list *our_env)
{
	char	**s;
	int		i;
	int		j;

	i = 0;
	s = fill_tab_strings(our_env);
	while (s[i])
	{
		j = i + 1;
		while (s[j])
		{
			if (ft_strcmp(s[i], s[j]) > 0)
				ft_swap(&s[i], &s[j]);
			j++;
		}
		i++;
	}
	i = 0;
	export_alone2(i, s);
	free_strings(s);
	return (0);
}
