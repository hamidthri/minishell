/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:37:21 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/19 01:08:56 by htaheri          ###   ########.fr       */
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
		{
			return (i);
		}
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

int	var_exist(t_builtin *bltin, char *str)
{
	int	equal_index;
	int	i;

	equal_index = find_equal(str);
	i = 0;
	while (bltin->env[i])
	{
		if (!strncmp(bltin->env[i], str, equal_index)
			&& bltin->env[i][equal_index] == '=')
		{
			free(bltin->env[i]);
			bltin->env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**add_all_variable(char **env, char **new_env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (new_env[i] == NULL)
		{
			free_all(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	return (new_env);
}

char	**add_var(char **arr, char *str)
{
	size_t			i;
	char			**new_env;
	t_quote_parsed	q;
	int				f_des;
	char			*line;
	char			*map_str;

	i = 0;
	q = parse_quotes(str);
	if (q.end)
	{
		here_doc(&q.end, q.hint);
		f_des = open("tmp", O_RDONLY);
		line = get_next_line(f_des);
		map_str = ft_strjoin(q.str, line);
		while (1)
		{
			line = get_next_line(f_des);
			if (line)
			{
				map_str = ft_strjoin(map_str, line);
				free(line);
			}
			else
				break ;
		}
	}
	else
		map_str = str;
	while (arr[i] != NULL)
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env = add_all_variable(arr, new_env, map_str);
	return (new_env);
}

int	custom_export(t_builtin *bltin, char **str)
{
	int		i;
	char	**tmp;

	if (!str[1] || str[1][0] == '\0')
		return (EXIT_FAILURE);
	i = 1;
	while (str[i])
	{
		if (!invalid_parameter(str[i]) && !var_exist(bltin, str[i]))
		{
			tmp = add_var(bltin->env, str[i]);
			if (tmp)
			{
				free_all(bltin->env);
				bltin->env = tmp;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
