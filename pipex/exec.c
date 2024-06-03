/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:45:04 by aazra             #+#    #+#             */
/*   Updated: 2022/04/05 17:52:56 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_path(t_list *our_env)
{
	t_list	*tmp;

	tmp = our_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "PATH=", 5) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char	**fill_tab_strings(t_list *our_env)
{
	int		nb;
	int		i;
	char	**s;
	t_list	*temp;

	temp = our_env;
	i = 0;
	nb = ft_lstsize(temp);
	s = (char **)malloc(sizeof(char *) * (nb + 1));
	while (our_env)
	{
		s[i] = (char *)malloc(sizeof(char) * (ft_strlen(our_env->content) + 1));
		ft_strlcpy(s[i], our_env->content, ft_strlen(our_env->content) + 1);
		i++;
		our_env = our_env->next;
	}
	s[i] = NULL;
	return (s);
}

void	exec_basic_cmd_3(t_cmd **c, t_list *our_env, char **s)
{
	int	i;

	i = 0;
	if (check_slash(c[0]->cmd[0]))
		i = cond_slash2(c, c[0]->cmd, c[0]->cmd[0], s);
	if (env_path(our_env) == 0 && is_builtin(c, 0) == 0
		&& check_slash(c[0]->cmd[0]) == 0)
	{
		if (execve(c[0]->cmd[0], c[0]->cmd, s) < 0)
			i = print_error2(c, c[0]->cmd[0]);
	}
	freecmdexe(c);
	free_env(our_env);
	free_strings(s);
	exit(i);
}

void	exec_basic_cmd_2(t_cmd **c, t_list *our_env, char **s, char *path)
{
	if (c[0]->fdout > 2)
	{
		dup2(c[0]->fdout, STDOUT_FILENO);
		close(c[0]->fdout);
	}
	else if (c[0]->fdout == -1)
		exit(exitfd(c, our_env, s));
	if (c[0]->command == 0)
		exit(exitvide(c, our_env, s));
	if (c[0]->cmd[0][0] == '\0')
		exitnull(c, our_env, s);
	if (env_path(our_env) == 1 && is_builtin(c, 0) == 0
		&& check_slash(c[0]->cmd[0]) == 0)
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
	exec_basic_cmd_3(c, our_env, s);
}

int	exec_basic_cmd(t_cmd **c, t_list *our_env)
{
	char	*path;
	int		pid;
	int		status;
	char	**s;

	path = NULL;
	s = fill_tab_strings(our_env);
	status = 0;
	pid = 0;
	pid = fork();
	if (pid == 0)
	{
		cond_pipe(c, 0);
		if (c[0]->fdin == -1)
			exit(exitfd(c, our_env, s));
		exec_basic_cmd_2(c, our_env, s, path);
		exit(0);
	}
	waitpid(pid, &status, 0);
	free_strings(s);
	if (is_builtin(c, 0) == 1)
		return (use_builtin(c, our_env, 0));
	return (WEXITSTATUS(status));
}
