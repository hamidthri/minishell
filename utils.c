/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:49:12 by htaheri           #+#    #+#             */
/*   Updated: 2023/11/30 18:25:41 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(char **v)
{
	char	**start;

	start = v;
	while (*v)
	{
		free(*v);
		v++;
	}
	free(start);
}

char	**env_dup(char	**envp)
{
	char	**arr;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	arr = ft_calloc((i + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		arr[i] = ft_strdup(envp[i]);
		if (!arr[i])
		{
			free_all(arr);
			return (NULL);
		}
		i++;
	}
	return (arr);
}


void	find_pwd(t_builtin *bltin)
{
	int		i;

	i = 0;
	while (bltin->env[i])
	{
		if (!ft_strncmp(bltin->env[i], "PWD=", 4))
		{
			bltin->pwd = ft_substr(bltin->env[i], 4,
					ft_strlen(bltin->env[i]) - 4);
		}
		if (!ft_strncmp(bltin->env[i], "OLDPWD=", 7))
		{
			bltin->oldpwd = ft_substr(bltin->env[i], 7,
					ft_strlen(bltin->env[i]) - 7);
		}
		i++;
	}
}

void	get_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
}
