/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 11:23:38 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 09:42:26 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rediroutf(int *n, int c, char *path)
{
	int	fd;

	if (c == APPND)
		fd = open(path, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (c == REDIROUT)
		fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (errno != 0 && fd == -1 && *n != 1)
	{
		write(2, "Minishell: ", ft_strlen("Minishell: "));
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		*n = 1;
	}
	return (fd);
}

int	redirinf(int *n, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1 && *n != 1)
	{
		write(2, "Minishell: ", ft_strlen("Minishell: "));
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		*n = 1;
	}
	if (*n == -1)
		fd = -1;
	return (fd);
}

int	redircheck(int *n, int c, char *path, t_list *env)
{
	char	*check;
	int		i;
	int		z;

	check = ft_strdup(path);
	z = checkmot(path, 0, 0, 0);
	if (z > 0)
	{
		free(check);
		check = changeword(path, z, env);
	}
	if (z == 2 && ft_strlen(check) == 0)
	{
		free(check);
		write(2, "Minishell: ", ft_strlen("Minishell: "));
		write(2, path, ft_strlen(path));
		write(2, ": ambiguous redirect\n", ft_strlen(": ambiguous redirect\n"));
		return (-1);
	}
	if (c == APPND || c == REDIROUT)
		i = rediroutf(n, c, check);
	if (c == REDIRIN)
		i = redirinf(n, check);
	free(check);
	return (i);
}
