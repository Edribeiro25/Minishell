/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 11:01:23 by aazra             #+#    #+#             */
/*   Updated: 2022/04/05 01:13:51 by aazra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(char *s)
{
	char	*s2;
	char	*s1;
	int		d;

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
	exit (d);
}

int	ft_atoi(const char *nptr)
{
	long	i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * result);
}

unsigned long long	valeur_absolue(long long nb)
{
	if (nb >= 0)
		return (nb);
	else
		return (-nb);
}

long long	ft_atoi_long(const char *nptr)
{
	long long	i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\f' || nptr[i] == '\r' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (sign * result);
}
