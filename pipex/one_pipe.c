/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:35:50 by aazra             #+#    #+#             */
/*   Updated: 2022/04/05 17:53:54 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	launch_cmd1_2(t_cmd **c, t_struct *s, t_list *our_env, char **s1)
{
	if (check_slash(c[0]->cmd[0]))
		cond_slash(c, 0, s1, our_env);
	if (env_path(our_env) == 1 && is_builtin(c, 0) == 0
		&& check_slash(c[0]->cmd[0]) == 0)
	{
		s->path1 = set_path(s->cmd1[0], s1, 0);
		if (s->path1 == NULL)
			cmd1_error(c, s1, c[0]->cmd[0], our_env);
		if (execve(s->path1, s->cmd1, s1) < 0)
		{
			if (s->path1)
				free(s->path1);
		}
	}
	else if ((env_path(our_env) == 0 && check_slash(c[0]->cmd[0]) == 0)
		&& is_builtin(c, 0) == 0)
	{
		if (execve(c[0]->cmd[0], c[0]->cmd, s1) < 0)
			print_error2(c, c[0]->cmd[0]);
	}
	free_strings(s1);
	if (is_builtin(c, 0) == 1)
		use_builtin(c, our_env, 0);
}

void	launch_cmd1(t_cmd **c, t_struct *s, t_list *our_env)
{
	char	**s1;

	s1 = fill_tab_strings(our_env);
	s->cmd1 = c[0]->cmd;
	cond_pipe(c, 0);
	if (c[0]->fdin == -1)
		exit(exitfd(c, our_env, s1));
	if (c[0]->fdout > 2)
	{
		dup2(c[0]->fdout, STDOUT_FILENO);
		close(c[0]->fdout);
	}
	else if (c[0]->fdout == -1)
		exit(exitfd(c, our_env, s1));
	else
		dup2(s->pipefd[1], STDOUT_FILENO);
	if (c[0]->command == 0)
		exit(exitvide(c, our_env, s1));
	if (c[0]->cmd[0][0] == '\0')
		write(2, "command not found : ''\n", 23);
	launch_cmd1_2(c, s, our_env, s1);
	freecmdexe(c);
	free_env(our_env);
	exit(0);
}

int	launch_cmd2_2(t_cmd **c, t_struct *s, t_list *our_env, char **s2)
{
	int	i;

	i = 0;
	if (env_path(our_env) == 1 && is_builtin(c, 1) == 0
		&& check_slash(c[1]->cmd[0]) == 0)
	{
		s->path2 = set_path(s->cmd2[0], s2, 0);
		if (s->path2 == NULL)
			cmd2_error(c, s2, c[1]->cmd[0], our_env);
		if (execve(s->path2, s->cmd2, s2) < 0)
		{
			if (s->path2)
				free(s->path2);
		}
	}
	else if ((env_path(our_env) == 0 && check_slash(c[1]->cmd[0]) == 0)
		&& is_builtin(c, 1) == 0)
	{
		if (execve(c[1]->cmd[0], c[1]->cmd, s2) < 0)
			return (print_error2(c, c[1]->cmd[0]));
	}
	free_strings(s2);
	launch_cmd2_3(c, our_env);
	return (i);
}

void	launch_cmd2(t_cmd **c, t_struct *s, t_list *our_env)
{
	char	**s2;

	s2 = fill_tab_strings(our_env);
	s->cmd2 = c[1]->cmd;
	cond_pipe(c, 1);
	if (c[1]->fdin == -1)
		exit(exitvide(c, our_env, s2));
	else
		dup2(s->pipefd[0], STDIN_FILENO);
	if (c[1]->fdout > 2)
	{
		dup2(c[1]->fdout, STDOUT_FILENO);
		close(c[1]->fdout);
	}
	else if (c[1]->fdout == -1)
		exit(exitfd(c, our_env, s2));
	if (c[1]->command == 0)
		exit(exitvide(c, our_env, s2));
	if (c[1]->cmd[0][0] == '\0')
		exitnull(c, our_env, s2);
	if (check_slash(c[1]->cmd[0]))
		cond_slash(c, 1, s2, our_env);
	exit(launch_cmd2_2(c, s, our_env, s2));
}

int	one_pipe(t_cmd **c, t_list *our_env)
{
	t_struct	s;
	int			status;

	initialize_struct(&s);
	if (pipe(s.pipefd) == -1)
		global_error("Error : pipe failed", 1);
	s.pid1 = fork();
	if (s.pid1 == 0)
		launch_cmd1(c, &s, our_env);
	close(s.pipefd[1]);
	s.pid2 = fork();
	if (s.pid2 == 0)
		launch_cmd2(c, &s, our_env);
	close(s.pipefd[0]);
	waitpid(s.pid1, NULL, 0);
	waitpid(s.pid2, &status, 0);
	return (WEXITSTATUS(status));
}
