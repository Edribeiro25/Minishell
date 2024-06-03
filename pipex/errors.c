/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazra <aazra@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:29:42 by aazra             #+#    #+#             */
/*   Updated: 2022/04/04 22:08:48 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	global_error(char *str, int exit_or_not)
{
	if (errno)
		perror(str);
	else
		ft_putstr_fd(str, 2);
	if (exit_or_not == 1)
		exit(EXIT_FAILURE);
}

void	cmd1_error(t_cmd **c, char **s, char *string, t_list *our_env)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("command not found : ", string);
	s2 = ft_strjoin(s1, "\n");
	write(2, s2, ft_strlen(s2));
	free(s1);
	free(s2);
	freecmdexe(c);
	free_strings(s);
	free_env(our_env);
	exit(127);
}

void	cmd2_error(t_cmd **c, char **s, char *string, t_list *our_env)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("command not found : ", string);
	s2 = ft_strjoin(s1, "\n");
	write(2, s2, ft_strlen(s2));
	free(s1);
	free(s2);
	freecmdexe(c);
	free_strings(s);
	free_env(our_env);
	exit(127);
}

void	cmd_error(t_cmd **c, char **s, char *string, t_list *our_env)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin("command not found : ", string);
	s2 = ft_strjoin(s1, "\n");
	write(2, s2, ft_strlen(s2));
	free(s1);
	free(s2);
	freecmdexe(c);
	free_env(our_env);
	free_strings(s);
	exit(127);
}

void	path_error(char **big_path, char *temp)
{
	if (temp)
		free(temp);
	if (big_path)
		free_paths(big_path, NULL);
	global_error("Error : malloc failed", 1);
}
