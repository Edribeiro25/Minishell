# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eribeiro <eribeiro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/28 08:25:17 by eribeiro          #+#    #+#              #
#    Updated: 2022/04/05 17:41:27 by eribeiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =          minishell

PARSING = main.c lexer.c utils1.c dol2.c check2.c signal.c lexer2.c tokenizer.c syntaxcheck.c redir.c cutcmd1.c cutcmd2.c quote.c ft_itoa.c freestruct.c fkdol.c check.c redir2.c

PIPEX = errors.c free.c ft_putstr_fd.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strnstr.c ft_substr.c path.c ft_strlcat.c ft_strncmp.c multiple_pipes.c multiple_pipes_2.c multiple_pipes_3.c exec.c one_pipe.c cond_slash.c

HERE =  udol.c doc.c dol_here.c newdol.c util2.c util3.c utils4.c

BUILTINS = builtins.c env.c lst.c lst2.c export.c export2.c ft_strlcpy.c ft_atoi.c exit.c cd.c unset.c pwd.c ft_isalnum.c llmin_exit.c

SRCS =          $(addprefix parsing/, $(PARSING)) \
		$(addprefix pipex/, $(PIPEX)) \
		$(addprefix builtins/, $(BUILTINS))\
		$(addprefix heredoc/, $(HERE)) 


OBJS =          $(SRCS:%.c=%.o)

CFLAGS =       	-Wall -Wextra -Werror -g

all:            $(NAME)

$(NAME):    $(OBJS)
	clang -g -o $(NAME) $(OBJS) -lreadline

clean:
	rm -rf $(OBJS)

fclean:         clean
	rm -rf $(NAME)

re:                     fclean all

.PHONY:                 all fclean clean re
