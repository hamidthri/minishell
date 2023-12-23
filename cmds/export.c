/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:37:21 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/23 18:29:42 by htaheri          ###   ########.fr       */
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

int	valid_identifier(char c)
{
	return (ft_strchr("|<>[],.:/{}/+^%#@!~=-?&*", c) != NULL);
}

int	invalid_parameter(char *str)
{
	int	i;

	if (ft_isdigit(str[0]) || str[0] == '=' || find_equal(str) == -1)
		return (terminate("export", "is not a valid identifier"), 1);
	i = 0;
	while (str[i] != '=')
	{
		if (valid_identifier(str[i]))
			return (terminate("export", "is not a valid identifier"), 1);
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

void	ft_export(char **vec, char ***env)
{
	int		i;
	char	**tmp;

	if (!vec[1] || vec[1][0] == '\0')
		return ;
	i = 1;
	while (vec[i])
	{
		tmp = ft_split(vec[i], '=');
		if (!invalid_parameter(vec[i]) && !var_exist(*env, tmp[0]))
		{
			if (!tmp[1])
				tmp[1] = ft_strdup("");
			set_env(env, tmp[0], tmp[1]);
		}
		i++;
	}
}
