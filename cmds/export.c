/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:37:21 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/21 22:51:06 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	error_handle(char *str)
{
	ft_putstr_fd("Minishell: export: ", STDERR_FILENO);
	if (str)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd("is not a valid identifier\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	valid_identifier(char c)
{
	return (ft_strchr("|<>[],.:/{}/+^%#@!~=-?&*", c) != NULL);
}

int	invalid_parameter(char *str)
{
	int	i;

	if (ft_isdigit(str[0]) || str[0] == '=' || find_equal(str) == -1)
		return (error_handle(str));
	i = 0;
	while (str[i] != '=')
	{
		if (valid_identifier(str[i]))
			return (error_handle(str));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	var_exist(char **env, char *str)
{
	int	equal_index;
	int	i;

	equal_index = find_equal(str);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, equal_index)
			&& env[i][equal_index] == '=')
		{
			set_env(&env, env[i], str);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export(char **str, char **env)
{
	int		i;
	char	**tmp;

	if (!str[1] || str[1][0] == '\0')
		return ;
	i = 1;
	while (str[i])
	{
		if (!invalid_parameter(str[i]) && !var_exist(env, str[i]))
		{
			tmp = ft_split(str[i], '=');
			set_env(&env, tmp[0], tmp[1]);
		}
		i++;
	}
}

