/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:16:48 by mmomeni           #+#    #+#             */
/*   Updated: 2023/11/15 16:48:14 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate(char *reason)
{
	perror(reason);
	exit(-1);
}

int	run(char *s)
{
	char	*file;
	int		n;
	char	**v;

	v = ft_split(s, ' ');
	if (v[0][0] == '/')
		file = ft_strdup(v[0]);
	else
		file = get_path(v[0]);
	n = execve(file, v, NULL);
	free(file);
	ft_free_split(v);
	return (n);
}

void	run_pipes(int fd[2], char **commands, int n)
{
	pid_t	pid;
	int		status;

	while (n-- > 1 && *commands)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			run(*commands);
			terminate(*commands);
		}
		else
		{
			dup2(fd[0], 0);
			close(fd[1]);
			waitpid(pid, &status, 0);
		}
		commands++;
	}
	run(*commands);
	terminate(*commands);
}
