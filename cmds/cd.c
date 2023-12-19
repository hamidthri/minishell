/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:22:12 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/20 00:10:35 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_path(char **env)
{
	set_env(&env, "OLD_PWD", get_env(env, "PWD"));
	set_env(&env, "PWD", getcwd(NULL, 0));
}

int	find_dir(char **env, char *s)
{
	char	*dir;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], s, ft_strlen(s)))
			dir = env[i] + ft_strlen(s);
		i++;
	}
	j = chdir(dir);
	if (j != 0)
	{
		ft_putstr_fd(s, STDERR_FILENO);
		ft_putstr_fd("Not Found", STDERR_FILENO);
		perror(" ");
	}
	return (j);
}

void	path_to_env(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", get_env(env, "PWD"));
			// free(env[i]);
			env[i] = tmp;
		}
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			tmp = ft_strjoin("OLDPWD=", get_env(env, "PWD"));
			// free(env[i]);
			env[i] = tmp;
		}
		i++;
	}
}

void	ft_cd(char **env, char *cmd_opt)
{
	int		j;

	if (!cmd_opt)
		j = find_dir(env, "HOME=");
	else if (!ft_strncmp(cmd_opt, "-", 1))
		j = find_dir(env, "OLDPWD=");
	else
	{
		j = chdir(cmd_opt);
		if (j != 0)
		{
			ft_putstr_fd("MiniShell: ", STDERR_FILENO);
			ft_putstr_fd(cmd_opt, STDERR_FILENO);
			perror(" ");
		}
	}
	if (j != 0)
		return ;
	new_path(env);
	path_to_env(env);
}
