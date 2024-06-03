/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazra <aazra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:31:09 by aazra             #+#    #+#             */
/*   Updated: 2022/03/31 12:08:59 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strings(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_paths(char **big_path, char *temp)
{
	int	i;

	i = 0;
	if (big_path)
	{
		while (big_path[i])
		{
			free(big_path[i]);
			i++;
		}
		free(big_path);
	}
	if (temp)
		free(temp);
}

void	free_temps(char *temp, char *small_path)
{
	if (temp)
		free(temp);
	if (small_path)
		free(small_path);
}

void	close_fds(t_pipe *p, t_cmd **c)
{
	int	i;

	i = 0;
	while (i < c[0]->pipe)
	{
		close(p->pfd[i][1]);
		close(p->pfd[i][0]);
		i++;
	}
}

void	free_pipes(t_pipe *p, t_cmd **c)
{
	int	i;

	i = 0;
	while (i < c[0]->pipe)
	{
		free(p->pfd[i]);
		i++;
	}
	free(p->pfd);
}
