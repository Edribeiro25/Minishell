/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:46:32 by aazra             #+#    #+#             */
/*   Updated: 2022/04/05 13:14:26 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	middle_child_3(t_cmd **c, t_list *our_env, int i, char **s)
{
	char	*path;

	if (check_slash(c[i]->cmd[0]))
		cond_slash(c, i, s, our_env);
	if (env_path(our_env) == 1 && is_builtin(c, i) == 0)
	{
		path = set_path(c[i]->cmd[0], s, 0);
		if (path == NULL)
			cmd_error(c, s, c[i]->cmd[0], our_env);
		if (execve(path, c[i]->cmd, s) < 0)
		{
			if (path)
				free(path);
		}
	}
	else if (env_path(our_env) == 0 && is_builtin(c, i) == 0)
	{
		if (execve(c[i]->cmd[0], c[i]->cmd, s) < 0)
			print_error2(c, c[i]->cmd[0]);
	}
}

void	middle_child_2(t_cmd **c, t_pipe *p, int i)
{
	if (c[i]->fdin > 2)
	{
		dup2(c[i]->fdin, STDIN_FILENO);
		close(c[i]->fdin);
	}
	else if (c[i]->fdin == -1)
		exit(0);
	else
		dup2(p->pfd[i - 1][0], STDIN_FILENO);
	if (c[i]->fdout > 2)
	{
		dup2(c[i]->fdout, STDOUT_FILENO);
		close(c[i]->fdout);
	}
	else if (c[i]->fdout == -1)
		exit(0);
	else
		dup2(p->pfd[i][1], STDOUT_FILENO);
	if (c[i]->cmd[0][0] == '\0')
		write(2, "command not found : ''\n", 23);
}

void	middle_child(t_cmd **c, t_pipe *p, t_list *our_env, int i)
{
	int		pid;
	char	**s;

	pid = fork();
	if (pid == -1)
		perror("fork failed");
	if (pid == 0)
	{
		s = fill_tab_strings(our_env);
		if (c[i]->command == 0)
			exit(exitvide(c, our_env, s));
		middle_child_2(c, p, i);
		close_fds(p, c);
		if (c[i]->cmd[0])
			middle_child_3(c, our_env, i, s);
		free_pipes(p, c);
		free_strings(s);
		if (is_builtin(c, i) == 1)
			use_builtin(c, our_env, i);
		free_env(our_env);
		freecmdexe(c);
		exit(0);
	}
}
