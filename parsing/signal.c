/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 08:59:25 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/03 18:28:17 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle(int sig)
{
	if (sig == SIGINT && g_exit_status == -1)
	{
		write(1, "\n", 1);
		exit(130);
	}
	if (sig == SIGINT && g_exit_status == -3)
		return ;
	if (sig == SIGINT && g_exit_status == -2)
	{
		write(1, "\n", 1);
		g_exit_status = 130;
		return ;
	}
	if (sig == SIGINT && g_exit_status != -1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	handlequit(int sig)
{
	if (sig == SIGQUIT && g_exit_status == -2)
	{
		write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
		g_exit_status = 131;
	}
}

void	setsig(int i)
{
	if (i == 1)
		signal(SIGQUIT, &handlequit);
	if (i == 0)
		signal(SIGQUIT, SIG_IGN);
}
