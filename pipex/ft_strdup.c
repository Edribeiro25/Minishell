/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:09:51 by aazra             #+#    #+#             */
/*   Updated: 2022/04/05 17:55:01 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(char *s)
{
	int		i;
	size_t	size;
	char	*result;

	i = 0;
	size = ft_strlen(s);
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	while (s[i] != '\0')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	exitfd(t_cmd **c, t_list *our_env, char **s)
{
	freecmdexe(c);
	free_env(our_env);
	free_strings(s);
	return (1);
}

int	exitvide(t_cmd **c, t_list *our_env, char **s)
{
	freecmdexe(c);
	free_env(our_env);
	free_strings(s);
	return (0);
}

void	exitnull(t_cmd **c, t_list *our_env, char **s)
{
	write(2, "command not found : ''\n", 23);
	freecmdexe(c);
	free_env(our_env);
	free_strings(s);
	exit(127);
}
