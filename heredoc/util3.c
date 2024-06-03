/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 12:54:39 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/04 12:59:18 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	envdol1(char *s, int *i)
{
	int	d;

	d = *i + 1;
	if (s[d] == '?')
	{
		*i = d + 1;
		return ;
	}
	while (ft_isalnum(s[d]) || s[d] == '_')
	{
		if (s[d] >= '0' && s[d] <= '9' && s[d - 1] == '$')
		{
			d++;
			break ;
		}
		d++;
	}
	*i = d;
}

void	nondol1(char *s, int *i)
{
	int	d;

	d = *i;
	while (s[d] != '\0' && s[d] != '$')
		d++;
	*i = d;
}

void	rempmycl(char **tmp, char *s, t_list *env)
{	
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$' && isdol(s[i + 1]) == 0)
		{
			tmp[c] = sdol(&i);
			c++;
		}
		if (s[i] == '$' && isdol(s[i + 1]) == 1)
		{
			tmp[c] = envdol(s, &i, env);
			c++;
		}
		if (s[i] != '$' && s[i] != '\0')
		{
			tmp[c] = nondol(s, &i);
			c++;
		}
	}
	tmp[c] = NULL;
}

char	*doluni(char *s, int i, t_list *env)
{
	char	**tmp;
	char	*tmp1;
	int		c;

	c = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$')
		{
			c++;
			envdol1(s, &i);
		}
		if (s[i] != '$' && s[i] != '\0')
		{
			c++;
			nondol1(s, &i);
		}
	}
	tmp = malloc(sizeof(char *) * (c + 1));
	if (!tmp)
		return (NULL);
	rempmycl(tmp, s, env);
	tmp1 = rejoins(tmp, c);
	freetab(tmp, c);
	return (tmp1);
}

int	checkdoll(char *s)
{
	int	i ;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] != '\0' && ft_isalnum(s[i + 1]))
			return (1);
		if (s[i] == '$' && s[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}
