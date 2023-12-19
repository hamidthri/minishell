/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:11:18 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/20 00:05:57 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

void			run_pipes(int fd[2], char **commands, int n);
void			terminate(char *cmd, char *reason);

char			*get_env(char **env, char *key);
void			set_env(char ***env, char *key, char *value);
char			*get_path(char *program);

char			*parse(char *s, char **env);
void			print_vec(char **vec);
int				here_doc(char *end, char *hint);

typedef struct s_quote_parsed
{
	char		*str;
	char		end;
	char		*hint;
}				t_quote_parsed;

t_quote_parsed	parse_quotes(const char *s);

/* Builtins */
void			ft_echo(char **env, char **v);
void			ft_cd(char **env, char **v);
void			ft_pwd(void);
void			ft_export(char **env, char **v);
void			ft_unset(char **env, char **v);
void			ft_env(char **env, char **v);
void			ft_exit(char **env, char **v);

#endif
