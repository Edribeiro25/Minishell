/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 19:30:48 by eribeiro          #+#    #+#             */
/*   Updated: 2022/04/05 17:55:33 by eribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define  MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define WORD 1
# define PIPE 2
# define CSPACE 3
# define REDIROUT 4
# define APPND 5
# define REDIRIN 6
# define HERED 7
# define NEWL 8
# define IMAX 2147483647
# define IMIN -2147483648

extern int	g_exit_status;

typedef struct s_lex
{
	char	*mot;
	int		tok;
}		t_lex;

typedef struct s_cmd
{
	int		command;
	int		pipe;
	char	**cmd;
	int		fdin;
	int		fdout;
	int		here;
	int		rerror;
	int		exitstat;
}		t_cmd;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}		t_list;

typedef struct s_doc
{
	t_cmd		**c;
	t_lex		*lex;
}		t_doc;

typedef struct s_here_doc
{
	char		**c;
	int			*pipe;
	int			errorcode;
	t_list		*env;
	t_doc		he;
	char		**here;
}		t_here;
void				handle(int sig);
void				handlequit(int sig);
void				setsig(int i);
//parsing
void				listfree(void *mem);
void				checkcmd(t_cmd **tmp, t_list *env);
void				freetab(char **l, int i);
void				redirinter(t_lex *l, t_cmd *c, t_list *e, int i);
void				freecmdexe(t_cmd **c);
void				psyntaxerror(int p);
int					onlyspace(char *line);
int					parsing(t_lex *l, t_cmd **c, t_list *e);
int					wordsep(char *l, int i, int *ctw);
int					spacesep(char *l, int i);
int					redircheck(int *n, int c, char *path, t_list *env);
int					utword2(char *s, char **cl, int p);
int					checkquote(t_lex *lex);
int					closequote(char *l, char c, int *i);
int					syntaxerror(t_lex *lex);
int					countword2(char *s);
int					redirin(t_lex *l, t_cmd **c, t_list *e, int i);
int					redirout(t_lex *l, t_cmd **c, t_list *e, int i);
int					ft_isalnum(char c);
int					ft_strlen2(char *s);
int					ctword(char **l);
int					heredoc(t_lex *l, t_cmd **c, t_list *e, int i);
int					check_sep(char c);
int					countword(char *l);
int					ignormeta(char *l, int i, char w);
int					checkdoll(char *s);
int					redir(t_lex *l, t_cmd **c, t_list *e, int i);
int					cutword2(char *s, char **cl, int p);
char				**changecmd1(char **l, int *n, t_list *env);
char				*doluni(char *s, int i, t_list *env);
char				*ft_itoa(int n);
void				freelex(t_lex *lex);
char				*sdol(int *i);
char				*getdoll(char *s);
char				*supprquote(char *s, int i);
char				**cutword(char *l, int i);
char				*changeword(char *l, int c, t_list *env);
t_lex				*tokenizer(char **cl, int i);
t_cmd				**cutcmd2(t_lex *lex, int i, int r);
t_cmd				**createcmd(t_lex *lex, t_list *env);

// heredoc

char				**recupehere(t_lex *l, int *i, int co);
int					isdol(char c);
char				*sdol(int *i);
char				**recupehere(t_lex *l, int *i, int co);
void				heredone(t_here h);
char				*dolhere(char *s, int i, t_here h);
char				*get_var(char *s, t_list *env);
char				*cutmyenv(char *s);
char				*envdol(char *s, int *i, t_list *env);
char				*nondol(char *s, int *i);
char				*rejoins(char **l, int i);
void				envdol1(char *s, int *i);
void				nondol1(char *s, int *i);
int					checkmot(char *s, int i, int doll, int quote);

//pipex
typedef struct s_struct
{
	int		pid1;
	int		pid2;
	int		pipefd[2];
	char	*path1;
	char	*path2;
	char	**cmd1;
	char	**cmd2;
}		t_struct;

typedef struct s_pipe
{
	int		**pfd;
	int		ac;
}		t_pipe;

size_t				ft_strlcpy(char *dst, const char *src, size_t size);
void				ft_putstr_fd(char *s, int fd);
char				**ft_split(char *s, char c);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strlen(char *s);
char				*ft_strnstr(char *big, char *little, size_t len);
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strdup(char *s);
void				global_error(char *str, int exit_or_not);
void				cmd1_error(t_cmd **c, char **s, char *string, \
					t_list *our_env);
void				cmd2_error(t_cmd **c, char **s, char *string, \
					t_list *our_env);
void				cmd_error(t_cmd **c, char **s, char *string, \
					t_list *our_env);
void				close_fds(t_pipe *p, t_cmd **c);
void				path_error(char **big_path, char *temp);
char				*set_temp(char **big_path, char *temp, int i);
char				*set_small_path(char **big_path, char *small_path, \
					char *s, char *temp);
char				*set_path(char *str, char **our_env, int i);
void				free_paths(char **big_path, char *temp);
void				free_temps(char *temp, char *small_path);
size_t				ft_strlcat(char *dst, char *src, size_t size);
int					ft_strncmp(char *s1, char *s2, size_t n);
int					multiple_pipes(t_cmd **data, t_list *our_env);
void				child1(t_cmd **c, t_pipe *p, t_list *our_env);
void				middle_child(t_cmd **c, t_pipe *p, t_list *our_env, int i);
int					exec_basic_cmd(t_cmd **c, t_list *our_env);
int					one_pipe(t_cmd **data, t_list *our_env);
void				initialize_struct(t_struct *s);
void				free_strings(char **s);
void				free_pipes(t_pipe *p, t_cmd **c);
int					exitvide(t_cmd **c, t_list *our_env, char **s);
int					exitfd(t_cmd **c, t_list *our_env, char **s);

//builtins
void				exitnull(t_cmd **c, t_list *our_env, char **s);
int					erreurnum(t_cmd **c, t_list *our_env, int i);
int					launch_cmd2_3(t_cmd **c, t_list *our_env);
int					ft_strcmp(char *s1, char *s2);
int					is_in_env(char *s, t_list *our_env);
int					is_builtin(t_cmd **c, int i);
int					use_builtin(t_cmd **data, t_list *our_env, int i);
int					mini_pwd_one(t_cmd **c, int i);
int					mini_pwd(void);
int					mini_echo(t_cmd **c, int i);
int					mini_echo_one(t_cmd **c, int i);
void				get_env(t_list **our_env, char **env);
int					mini_env_one(t_cmd **c, t_list *our_env, int i);
int					mini_env(t_list *our_env);
int					mini_export(t_cmd **c, t_list **our_env, int i);
int					export_alone(t_list *our_env);
int					mini_exit(t_cmd **data, t_list *our_env, int i);
int					mini_cd(t_cmd *c, t_list **env, int i);
int					mini_unset(t_cmd **c, t_list *our_env, int i);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstnew(void *content);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));
t_list				*ft_lstlast(t_list *lst);
void				cder(char *l);
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstadd_back(t_list **alst, t_list *new);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
int					ft_atoi(const char *nptr);
int					is_exit(t_cmd **data, int i);
void				free_env(t_list *our_env);
int					is_export(t_cmd **c, int i);
char				**fill_tab_strings(t_list *our_env);
int					env_path(t_list *our_env);
void				change_var_content(t_cmd **c, t_list **our_env, int j);
int					print_error_identifiant(t_cmd **c, int i);
int					print_error_fichier(t_cmd **c, int i);
int					print_error_export(t_cmd **c, int i, int j);
int					exit_error(t_cmd **c, int i);
int					print_error(char *s);
int					check_slash(char *s);
void				cond_slash(t_cmd **c, int i, char **s, t_list *our_env);
int					cond_slash2(t_cmd **c, char **cmd, char *str, char **s);
int					print_error2(t_cmd **c, char *s);
long long			ft_atoi_long(const char *nptr);
unsigned long long	valeur_absolue(long long nb);
int					is_alnum(char *s);
void				mini_exit_final(t_cmd **c, t_list *our_env, int i);
void				triple_free(char **s, t_cmd **c, t_list *our_env);
void				llmin_exit(t_cmd **c, t_list *our_env, char *s);
int					check_llmin(char *s);
int					exitvide(t_cmd **c, t_list *our_env, char **s);
char				*delete_spaces(char *s, int i);
void				cond_pipe(t_cmd **c, int i);
int					exitsimple(t_cmd **c, t_list *our_env, int i);
int					checknb(char *s);
int					nb(char s);
#endif
