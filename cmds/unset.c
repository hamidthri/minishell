/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:55:44 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/20 00:01:02 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**remove_variable(char **env, char *str)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, ft_strlen(str)) != 0
			|| env[i][ft_strlen(str)] != '=')
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j++])
			{
				ft_vecfree(new_env);
				return (NULL);
			}
		}
		i++;
	}
	return (new_env);
}

void	ft_unset(char **env, char **str)
{
	char	**new_env;

	if (!str[1])
	{
		ft_putendl_fd("Minishell: not enough arguments", STDERR_FILENO);
		return ;
	}
	new_env = remove_variable(env, str[1]);
	if (!new_env)
	{
		ft_putendl_fd("Minishell: unset failed", STDERR_FILENO);
		return ;
	}
	ft_vecfree(env);
	bltin->env = new_env;
}
