/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:58:02 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 16:35:19 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_error(t_cmd **c, int i)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("Minishell: exit: ", c[i]->cmd[1]);
	s2 = ft_strjoin(s1, ": argument numérique nécessaire\n");
	write(2, s2, ft_strlen(s2));
	free(s1);
	free(s2);
	return (0);
}

int	print_error_identifiant(t_cmd **c, int i)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("Minishell: ", c[i]->cmd[0]);
	s2 = ft_strjoin(s1, ": identifiant non valable\n");
	write(2, s2, ft_strlen(s2));
	free(s1);
	free(s2);
	if (errno == 13 || errno == 20)
		return (126);
	else if (errno == 2)
		return (127);
	return (0);
}

int	print_error_fichier(t_cmd **c, int i)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("Minishell: ", c[i]->cmd[0]);
	s2 = ft_strjoin(s1, ": est un dossier\n");
	write(2, s2, ft_strlen(s2));
	free(s1);
	free(s2);
	if (errno == 13 || errno == 20)
		return (126);
	else if (errno == 2)
		return (127);
	return (0);
}

int	mini_pwd_one(t_cmd **c, int i)
{
	char	loc[1024];

	if (getcwd(loc, sizeof(loc)) != NULL)
	{
		write(c[i]->fdout, loc, ft_strlen(loc));
		write(c[i]->fdout, "\n", 1);
		return (0);
	}
	else
		perror("pwd\n");
	return (-1);
}

int	mini_pwd(void)
{
	char	loc[1024];

	if (getcwd(loc, sizeof(loc)) != NULL)
	{
		write(1, loc, ft_strlen(loc));
		write(1, "\n", 1);
		return (0);
	}
	else
		perror("pwd\n");
	return (-1);
}
