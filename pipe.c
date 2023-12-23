/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:16:48 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/23 17:55:57 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_fd[2] = {0, 1};

static void	run_builtin(char **v, char ***env)
{
	if (!ft_strcmp(v[0], "echo"))
		ft_echo(v);
	else if (!ft_strcmp(v[0], "cd"))
		ft_cd(v, env);
	else if (!ft_strcmp(v[0], "pwd"))
		ft_putendl_fd(get_env(*env, "PWD"), 1);
	else if (!ft_strcmp(v[0], "export"))
		ft_export(v, env);
	else if (!ft_strcmp(v[0], "unset"))
		set_env(env, v[1], NULL);
	else if (!ft_strcmp(v[0], "env"))
		print_vec(*env);
	else if (!ft_strcmp(v[0], "exit"))
		ft_exit(v);
	free(v);
}

static void	run(char *s, char ***env)
{
	char	*file;
	char	**v;
	char	**builtins;

	builtins = ft_split("echo cd pwd export unset env exit", ' ');
	v = ft_split(s, ' ');
	if (!v || !*v)
		return ;
	if (ft_vecget(builtins, v[0]))
		return (run_builtin(v, env));
	if (v[0][0] == '/')
		file = ft_strdup(v[0]);
	else
		file = get_path(v[0]);
	if (!file)
		return (terminate(v[0], "command not found"));
	if (execve(file, v, NULL) < 0)
		terminate(file, NULL);
	free(file);
	ft_vecfree(v);
}

void	pipe_child( int d[2], int pipefd[2], char *cmd, char ***env)
{
	int	is_not_last;
	int	in_fd;

	is_not_last = d[0];
	in_fd = d[1];
	if (in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (is_not_last)
	{
		dup2(pipefd[1], 1);
		close(pipefd[1]);
	}
	else if (g_fd[1] != 1)
		dup2(g_fd[1], 1);
	run(cmd, env);
}

void	pipe_parent(int *d[3], int pipefd[2])
{
	int	i;
	int	n;
	int	*in_fd;

	i = *d[0];
	n = *d[1];
	in_fd = d[2];
	if (*in_fd != g_fd[0])
		close(*in_fd);
	if (i < n - 1)
	{
		close(pipefd[1]);
		*in_fd = pipefd[0];
	}
	if (i == n - 1 && g_fd[1] != 1)
		close(g_fd[1]);
}

void	run_pipes(char **commands, int n, char ***env)
{
	int		pipefd[2];
	int		i;
	int		in_fd;
	int		status;

	i = -1;
	in_fd = g_fd[0];
	while (++i < n)
	{
		if (i < n - 1)
			pipe(pipefd);
		if (fork() == 0)
			pipe_child((int[2]){i < n - 1, in_fd}, pipefd, commands[i], env);
		else
			pipe_parent((int *[3]){&i, &n, &in_fd}, pipefd);
	}
	while (i--)
		wait(&status);
	set_env(env, "?", ft_itoa(WEXITSTATUS(status)));
}
