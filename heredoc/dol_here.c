/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dol_here.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:38:43 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/04 17:26:08 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*envdolh(char *s, int *d, int r)
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

char	*envdolhere(char *s, int *i, t_here h)
{
	char	*tmp;
	char	*c;
	int		r;
	int		d;

	d = *i + 1;
	if (s[d] == '?')
	{
		c = ft_itoa(h.errorcode);
		*i = d + 1;
		return (c);
	}
	tmp = envdolh(s, &d, 0);
	r = 0;
	*i = *i + 1;
	while (*i < d)
	{
		tmp[r] = s[*i];
		r++;
		*i = *i + 1;
	}
	c = get_var(tmp, h.env);
	free (tmp);
	return (c);
}

int	isdol(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '?' || c == '_')
		return (1);
	return (0);
}

void	getfdol(char **tmp, t_here h, char *s )
{
	int		i;
	int		c;

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
			tmp[c] = envdolhere(s, &i, h);
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

char	*dolhere(char *s, int i, t_here h)
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
	getfdol(tmp, h, s);
	tmp1 = rejoins(tmp, c);
	freetab(tmp, c);
	return (tmp1);
}
