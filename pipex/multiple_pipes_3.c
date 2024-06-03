/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 14:46:32 by aazra             #+#    #+#             */
/*   Updated: 2022/04/05 13:21:40 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	child2_3(t_cmd **c, t_list *our_env, char **s, char *path)
{
	if (c[c[0]->pipe]->cmd[0][0] == '\0')
	{
		write(2, "command not found : ''\n", 23);
		return (127);
	}
	if (check_slash(c[c[0]->pipe]->cmd[0]))
		cond_slash(c, c[0]->pipe, s, our_env);
	if (env_path(our_env) == 1 && is_builtin(c, c[0]->pipe) == 0)
	{
		path = set_path(c[c[0]->pipe]->cmd[0], s, 0);
		if (path == NULL)
			cmd_error(c, s, c[c[0]->pipe]->cmd[0], our_env);
		if (execve(path, c[c[0]->pipe]->cmd, s) < 0)
		{
			if (path)
				free(path);
		}
	}
	else if (env_path(our_env) == 0 && is_builtin(c, c[0]->pipe) == 0)
	{
		if (execve(c[c[0]->pipe]->cmd[0], c[c[0]->pipe]->cmd, s) < 0)
			return (print_error2(c, c[c[0]->pipe]->cmd[0]));
	}
	return (0);
}

void	child2_2(t_cmd **c, t_pipe *p, char **s, t_list *our_env)
{
	if (c[c[0]->pipe]->fdin > 2)
	{
		dup2(c[c[0]->pipe]->fdin, STDIN_FILENO);
		close(c[c[0]->pipe]->fdin);
	}
	else if (c[c[0]->pipe]->fdin == -1)
		exit(exitvide(c, our_env, s));
	else
		dup2(p->pfd[c[0]->pipe - 1][0], STDIN_FILENO);
	if (c[c[0]->pipe]->fdout > 2)
	{
		dup2(c[c[0]->pipe]->fdout, STDOUT_FILENO);
		close(c[c[0]->pipe]->fdout);
	}
	else if (c[c[0]->pipe]->fdout == -1)
		exit(exitfd(c, our_env, s));
	if (c[c[0]->pipe]->command == 0)
		exit(exitvide(c, our_env, s));
}

void	child2(t_cmd **c, t_pipe *p, t_list *our_env)
{
	char	*path;
	char	**s;
	int		i;

	i = 0;
	path = NULL;
	s = fill_tab_strings(our_env);
	child2_2(c, p, s, our_env);
	close_fds(p, c);
	if (c[c[0]->pipe]->cmd[0])
		i = child2_3(c, our_env, s, path);
	free_pipes(p, c);
	free_strings(s);
	if (is_builtin(c, c[0]->pipe) == 1)
		i = use_builtin(c, our_env, c[0]->pipe);
	free_env(our_env);
	freecmdexe(c);
	exit(i);
}

void	multiple_pipes_2(t_cmd **c, t_pipe *p)
{
	int	i;

	i = 0;
	p->pfd = (int **)malloc(sizeof(int *) * c[0]->pipe);
	if (!p->pfd)
		global_error("Error with malloc\n", 1);
	while (i < c[0]->pipe)
	{
		p->pfd[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(p->pfd[i]) == -1)
			global_error("Error : pipe failed", 1);
		i++;
	}
}

int	multiple_pipes(t_cmd **c, t_list *our_env)
{
	t_pipe	p;
	int		i;
	int		status;
	int		pid;

	multiple_pipes_2(c, &p);
	child1(c, &p, our_env);
	i = 0;
	while (i++ < c[0]->pipe - 1)
		middle_child(c, &p, our_env, i);
	pid = fork();
	if (pid == -1)
		perror("fork failed");
	if (pid == 0)
		child2(c, &p, our_env);
	close_fds(&p, c);
	free_pipes(&p, c);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
	{
	}
	return (WEXITSTATUS(status));
}
