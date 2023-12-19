/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_custom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:22:12 by htaheri           #+#    #+#             */
/*   Updated: 2023/11/30 18:34:01 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_path(t_builtin	*bltin)
{
	bltin->oldpwd = bltin->pwd;
	bltin->pwd = getcwd(NULL, 0);
}

int	find_dir(t_builtin *bltin, char *s)
{
	char	*dir;
	int		i;
	int		j;

	i = 0;
	while (bltin->env[i])
	{
		if (!ft_strncmp(bltin->env[i], s, ft_strlen(s)))
			dir = bltin->env[i] + ft_strlen(s);
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

void	path_to_env(t_builtin *bltin)
{
	int		i;
	char	*tmp;

	i = 0;
	while (bltin->env[i])
	{
		if (!ft_strncmp(bltin->env[i], "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", bltin->pwd);
			free(bltin->env[i]);
			bltin->env[i] = tmp;
		}
		if (!ft_strncmp(bltin->env[i], "OLDPWD=", 7))
		{
			tmp = ft_strjoin("OLDPWD=", bltin->oldpwd);
			free(bltin->env[i]);
			bltin->env[i] = tmp;
		}
		i++;
	}
}

int	cd_custom(t_builtin	*bltin, char *cmd_opt)
{
	int		j;

	if (!cmd_opt)
		j = find_dir(bltin, "HOME=");
	else if (!ft_strncmp(cmd_opt, "-", 1))
		j = find_dir(bltin, "OLDPWD=");
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
		return (EXIT_FAILURE);
	new_path(bltin);
	path_to_env(bltin);
	return (EXIT_SUCCESS);
}
