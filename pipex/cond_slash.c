/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond_slash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:16:45 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/04 21:51:13 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_slash(char *s)
{
	int		k;

	k = 0;
	if (s[k] == '.')
		return (1);
	while (s[k])
	{
		if (s[k] == '/')
			return (1);
		k++;
	}
	return (0);
}

void	cond_slash(t_cmd **c, int i, char **s, t_list *our_env)
{
	if (execve(c[i]->cmd[0], c[i]->cmd, s) < 0)
	{
		free_strings(s);
		free_env(our_env);
		exit(print_error2(c, c[i]->cmd[0]));
	}
	exit(0);
}

int	print_error2(t_cmd **c, char *s)
{
	char	*s2;
	char	*s1;
	int		d;

	(void)c;
	d = 0;
	s2 = ft_strjoin("Minishell: ", s);
	s1 = ft_strjoin(s2, ": ");
	free(s2);
	s2 = ft_strjoin(s1, strerror(errno));
	free(s1);
	s1 = ft_strjoin(s2, "\n");
	write(2, s1, ft_strlen(s1));
	free(s1);
	free(s2);
	if (errno == 13 || errno == 20)
		d = 126;
	else
		d = 127;
	return (d);
}

int	cond_slash2(t_cmd **c, char **cmd, char *str, char **s)
{
	if (check_slash(str) == 1)
	{
		if (execve(cmd[0], cmd, s) < 0)
			return (print_error2(c, cmd[0]));
	}
	return (0);
}
