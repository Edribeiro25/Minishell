/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:46:32 by aazra             #+#    #+#             */
/*   Updated: 2022/04/05 13:22:18 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child1_3(t_cmd **c, t_list *our_env, char **s)
{
	char	*path;

	if (check_slash(c[0]->cmd[0]))
		cond_slash(c, 0, s, our_env);
	if (env_path(our_env) == 1 && is_builtin(c, 0) == 0)
	{
		path = set_path(c[0]->cmd[0], s, 0);
		if (path == NULL)
			cmd_error(c, s, c[0]->cmd[0], our_env);
		if (execve(path, c[0]->cmd, s) < 0)
		{
			if (path)
				free(path);
		}
	}
	else if (env_path(our_env) == 0 && is_builtin(c, 0) == 0)
	{
		if (execve(c[0]->cmd[0], c[0]->cmd, s) < 0)
			print_error2(c, c[0]->cmd[0]);
	}
}

void	child1_2(t_cmd **c, t_pipe *p)
{
	if (c[0]->fdin > 2)
	{
		dup2(c[0]->fdin, STDIN_FILENO);
		close(c[0]->fdin);
	}
	else if (c[0]->fdin == -1)
		exit(0);
	if (c[0]->fdout > 2)
	{
		dup2(c[0]->fdout, STDOUT_FILENO);
		close(c[0]->fdout);
	}
	else if (c[0]->fdout == -1)
		exit(0);
	else
		dup2(p->pfd[0][1], STDOUT_FILENO);
	if (c[0]->cmd[0][0] == '\0')
		write(2, "command not found : ''\n", 23);
}

void	child1(t_cmd **c, t_pipe *p, t_list *our_env)
{
	int		pid;
	char	**s;

	pid = fork();
	if (pid == -1)
		perror("fork failed");
	if (pid == 0)
	{
		s = fill_tab_strings(our_env);
		if (c[0]->command == 0)
			exit(exitvide(c, our_env, s));
		child1_2(c, p);
		close_fds(p, c);
		if (c[0]->cmd[0])
			child1_3(c, our_env, s);
		free_strings(s);
		free_pipes(p, c);
		if (is_builtin(c, 0) == 1)
			use_builtin(c, our_env, 0);
		freecmdexe(c);
		free_env(our_env);
		exit(0);
	}
}
