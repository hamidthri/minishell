/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:16:48 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/20 16:08:25 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_builtin(char **v, char **env)
{
	// if (!ft_strcmp(v[0], "echo"))
	// 	ft_echo(v);
	// else if (!ft_strcmp(v[0], "cd"))
	// 	ft_cd(v, env);
	// else if (!ft_strcmp(v[0], "pwd"))
	// 	ft_pwd();
	// else if (!ft_strcmp(v[0], "export"))
	// 	ft_export(v, env);
	// else if (!ft_strcmp(v[0], "unset"))
	// 	ft_unset(v, env);
	// else if (!ft_strcmp(v[0], "env"))
	// 	ft_env(env);
	// else if (!ft_strcmp(v[0], "exit"))
	// 	ft_exit(v);
	(void)env;
	free(v);
}

static void	run(char *s, char **env)
{
	char	*file;
	char	**v;
	char	**builtins;

	builtins = ft_split("echo cd pwd export unset env exit", ' ');
	v = ft_split(s, ' ');
	if (!v || !*v)
		return ;
	if (v[0][0] == '/')
		file = ft_strdup(v[0]);
	else
		file = get_path(v[0]);
	if (!file)
	{
		if (ft_vecget(builtins, v[0]))
			return (run_builtin(v, env));
		else
			return (terminate(v[0], "command not found"));
	}
	if (execve(file, v, NULL) < 0)
		terminate(file, NULL);
	free(file);
	ft_vecfree(v);
}

void	run_pipes(int fd[2], char **commands, int n, char **env)
{
	int	i;
	int	pid;
	int	status;
	int	in_fd;

	i = 0;
	in_fd = 0;
	while (i < n)
	{
		if (i < n - 1)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (in_fd != 0)
			{
				dup2(in_fd, 0);
				close(in_fd);
			}
			if (i < n - 1)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}
			run(commands[i], env);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (in_fd != 0)
				close(in_fd);
			if (i < n - 1)
			{
				close(fd[1]);
				in_fd = fd[0];
			}
			waitpid(pid, &status, 0);
			set_env(&env, "?", ft_itoa(status));
		}
		i++;
	}
}
