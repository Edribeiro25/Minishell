/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 09:01:15 by eribeiro          #+#    #+#             */
/*   Updated: 2022/03/31 18:32:59 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_sep(char c)
{
	if (c == '|')
		return (1);
	if (c == ' ')
		return (2);
	if (c == '<' || c == '>')
		return (3);
	return (0);
}
