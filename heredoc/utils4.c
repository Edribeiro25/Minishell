/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:09:14 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/04 12:09:31 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	cutmyenv2(char *tmp, char *s)
{
	int		i;
	int		r;

	i = 0;
	r = 0;
	while (s[i] != '\0')
	{
		if (i == 0)
		{
			while (s[i] != '=')
				i++;
			i++;
		}
		tmp[r] = s[i];
		i++;
		r++;
	}
	tmp[r] = '\0';
}

char	*cutmyenv(char *s)
{
	char	*tmp;
	int		i;

	i = 0;
	while (s[i] != '=')
		i++;
	i++;
	if ((ft_strlen(s) - i) == 0)
	{
		free (s);
		return (ft_strdup(""));
	}
	tmp = malloc(sizeof(char) * ((ft_strlen(s) - i) + 1));
	if (!tmp)
		return (NULL);
	cutmyenv2(tmp, s);
	free(s);
	return (tmp);
}

char	*get_var(char *s, t_list *env)
{
	char	*tmp;
	t_list	*temp;

	temp = env;
	tmp = NULL;
	while (temp)
	{
		if (ft_strncmp(s, temp->content, ft_strlen(s)) == 0)
			tmp = ft_strdup(temp->content);
		temp = temp->next;
	}
	if (!tmp)
		return (NULL);
	tmp = cutmyenv(tmp);
	return (tmp);
}

char	*envdol3(char *s, int *d, int r)
{
	char	*tmp;

	while (ft_isalnum(s[*d]) || s[*d] == '_')
	{
		if (s[*d] >= '0' && s[*d] <= '9' && s[*d - 1] == '$')
		{
			r = 1;
			*d = *d + 1;
			break ;
		}
		*d = *d + 1;
		r++;
	}
	tmp = malloc(sizeof(char) * (r + 2));
	if (!tmp)
		return (NULL);
	tmp[r + 1] = '\0';
	tmp[r] = '=';
	return (tmp);
}

char	*envdol(char *s, int *i, t_list *env)
{
	char	*tmp;
	char	*c;
	int		r;
	int		d;

	r = 0;
	d = *i + 1;
	if (s[d] == '?')
	{
		c = ft_itoa(g_exit_status);
		*i = d + 1;
		return (c);
	}
	tmp = envdol3(s, &d, 0);
	r = 0;
	*i = *i + 1;
	while (*i < d)
	{
		tmp[r] = s[*i];
		r++;
		*i = *i + 1;
	}
	c = get_var(tmp, env);
	free (tmp);
	return (c);
}
