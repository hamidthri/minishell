/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:16:48 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/18 19:19:10 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run(char *s)
{
	char	*file;
	char	**v;

	v = ft_split(s, ' ');
	if (!v || !*v)
		return ;
	if (v[0][0] == '/')
		file = ft_strdup(v[0]);
	else
		file = get_path(v[0]);
	if (!file)
		return (terminate(s, "command not found"));
	if (execve(file, v, NULL) < 0)
		terminate(file, NULL);
	free(file);
	ft_vecfree(v);
}

void	run_pipes(int fd[2], char **commands, int n)
{
	int			i;
	int			pid;
	int			status;
	int			in_fd;
	extern char	**environ;

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
			run(commands[i]);
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
			set_env(&environ, "?", ft_itoa(status));
		}
		i++;
	}
}
