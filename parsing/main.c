/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 11:06:20 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 09:32:30 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status;

int	exec(t_cmd **c, t_list *our_env)
{
	int		d;

	d = 0;
	c[0]->exitstat = g_exit_status;
	g_exit_status = -2;
	setsig(1);
	if (c[0]->pipe == 0)
		d = exec_basic_cmd(c, our_env);
	if (c[0]->pipe == 1)
		d = one_pipe(c, our_env);
	if (c[0]->pipe > 1)
		d = multiple_pipes(c, our_env);
	return (d);
}

t_lex	*intrelex(char *l, int *c)
{
	int		i;
	char	**cl;
	t_lex	*lex;
	int		d;

	i = countword(l);
	cl = cutword(l, i);
	lex = tokenizer(cl, i);
	d = syntaxerror(lex);
	if (d != 0)
		psyntaxerror(d);
	*c = d;
	return (lex);
}

void	recepline(char *l, t_list *our_env)
{
	int		d;
	t_lex	*lex;
	t_cmd	**c;

	lex = intrelex(l, &d);
	free(l);
	if (d == 0)
	{
		c = createcmd(lex, our_env);
		d = parsing(lex, c, our_env);
		freelex(lex);
		if (d == 0)
			d = exec(c, our_env);
		if (g_exit_status != 130 && g_exit_status != 131)
			g_exit_status = d;
		freecmdexe(c);
	}
	else
		freelex(lex);
	setsig(0);
}

void	minishell(t_list **env)
{
	char	*line;

	while (1)
	{
		line = readline("Minishell $ ");
		if (line != NULL && onlyspace(line) == 1)
		{
			add_history(line);
			recepline(line, *env);
		}
		else if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
	}
	rl_clear_history();
	if (line)
		free(line);
}

int	main(int ac, char **av, char **env)
{
	t_list	*our_env;

	(void)ac;
	(void)av;
	g_exit_status = 0;
	our_env = NULL;
	get_env(&our_env, env);
	signal(SIGINT, &handle);
	setsig(0);
	minishell(&our_env);
	ft_lstclear(&our_env, listfree);
	return (0);
}
