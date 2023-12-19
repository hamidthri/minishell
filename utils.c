/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:49:12 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/18 20:05:33 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate(char *cmd, char *reason)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (reason)
		ft_putstr_fd(reason, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

int	here_doc(char *end, char *hint)
{
	char	*line;
	int		tmp_file;

	if (!end || !*end)
		return (terminate(NULL,
							"syntax error near unexpected token `newline'"),
				-1);
	tmp_file = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline(hint);
		if (!line || (ft_strlen(line) == ft_strlen(end) && !ft_strncmp(line,
					end, ft_strlen(end))))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, tmp_file);
		free(line);
		line = NULL;
	}
	dup2(tmp_file, 0);
	close(tmp_file);
	return (tmp_file);
}

void	print_vec(char **vec)
{
	int	i;

	i = 0;
	while (vec[i])
	{
		printf("[%s]\n", vec[i]);
		i++;
	}
}

// void	find_pwd(t_builtin *bltin)
// {
// 	int	i;

// 	i = 0;
// 	while (bltin->env[i])
// 	{
// 		if (!ft_strncmp(bltin->env[i], "PWD=", 4))
// 		{
// 			bltin->pwd = ft_substr(bltin->env[i], 4, ft_strlen(bltin->env[i])
// 					- 4);
// 		}
// 		if (!ft_strncmp(bltin->env[i], "OLDPWD=", 7))
// 		{
// 			bltin->oldpwd = ft_substr(bltin->env[i], 7, ft_strlen(bltin->env[i])
// 					- 7);
// 		}
// 		i++;
// 	}
// }

// void	get_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		ft_putendl_fd(envp[i], STDOUT_FILENO);
// 		i++;
// 	}
// }
