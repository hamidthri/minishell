/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:11:18 by mmomeni           #+#    #+#             */
/*   Updated: 2023/11/15 16:46:27 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

// -------- Pipex --------
/* System */

int		run(char *s);
void	terminate(char *reason);
void	run_pipes(int fd[2], char **commands, int n);

/* File System */

char	*get_env(char *key);
char	*join_path(char *s1, char *s2);
char	*get_path(char *program);
// -------- Pipex --------

void	history_add(char *cmd);

#endif
