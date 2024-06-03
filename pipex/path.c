/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:33:11 by aazra             #+#    #+#             */
/*   Updated: 2022/04/01 13:54:36 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialize_struct(t_struct *s)
{
	s->pid1 = -1;
	s->pid2 = -1;
	s->cmd1 = NULL;
	s->cmd2 = NULL;
	s->path1 = NULL;
	s->path2 = NULL;
}

char	*set_temp(char **big_path, char *temp, int i)
{
	temp = ft_strjoin(big_path[i], "/");
	if (temp == NULL)
		path_error(big_path, temp);
	return (temp);
}

char	*set_small_path(char **big_path, char *small_path, char *s, char *temp)
{
	small_path = ft_strjoin(temp, s);
	if (small_path == NULL)
		path_error(big_path, temp);
	return (small_path);
}

char	**set_path_2(char **big_path, char **our_env)
{
	int	i;

	i = 0;
	while (our_env[i])
	{
		if (ft_strnstr(our_env[i], "PATH=", 5))
		{
			big_path = ft_split(&our_env[i][5], ':');
			return (big_path);
		}
		i++;
	}
	return (NULL);
}

char	*set_path(char *str, char **our_env, int i)
{
	char	**big_path;
	char	*small_path;
	char	*temp;

	big_path = NULL;
	big_path = set_path_2(big_path, our_env);
	if (big_path != NULL)
	{
		while (big_path && big_path[i])
		{
			temp = set_temp(big_path, temp, i);
			small_path = set_small_path(big_path, small_path, str, temp);
			if (access(small_path, X_OK) != -1)
			{
				free_paths(big_path, temp);
				return (small_path);
			}
			i++;
			free_temps(temp, small_path);
		}
		free_paths(big_path, NULL);
	}
	return (NULL);
}
