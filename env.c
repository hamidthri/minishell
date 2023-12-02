/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:21:57 by mmomeni           #+#    #+#             */
/*   Updated: 2023/11/15 16:48:07 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *key)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], key, ft_strlen(key)))
			return (environ[i] + ft_strlen(key) + 1);
		i++;
	}
	return (NULL);
}

char	*join_path(char *s1, char *s2)
{
	char	*parent;
	char	*path;

	parent = ft_strjoin(s1, "/");
	path = ft_strjoin(parent, s2);
	free(parent);
	return (path);
}

char	*get_path(char *program)
{
	char	**v;
	char	*path;
	int		i;

	i = 0;
	v = ft_split(get_env("PATH"), ':');
	while (v[i])
	{
		path = join_path(v[i], program);
		if (!access(path, X_OK))
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	ft_free_split(v);
	return (NULL);
}
