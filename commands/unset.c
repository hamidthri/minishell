/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:55:44 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/19 01:05:16 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**remove_variable(t_builtin *bltin, char *str)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (bltin->env[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	// if (!new_env)
	// 	return (NULL);
	i = 0;
	while (bltin->env[i])
	{
		if (ft_strncmp(bltin->env[i], str, ft_strlen(str)) != 0
			|| bltin->env[i][ft_strlen(str)] != '=')
		{
			new_env[j] = ft_strdup(bltin->env[i]);
			if (!new_env[j++])
			{
				free_all(new_env);
				return (NULL);
			}
		}
		i++;
	}
	return (new_env);
}

void	custom_unset(t_builtin *bltin, char **str)
{
	char	**new_env;

	if (!str[1])
	{
		ft_putendl_fd("Minishell: not enough arguments", STDERR_FILENO);
		return ;
	}
	new_env = remove_variable(bltin, str[1]);
	if (!new_env)
	{
		ft_putendl_fd("Minishell: unset failed", STDERR_FILENO);
		return ;
	}
	free_all(bltin->env);
	bltin->env = new_env;
}
