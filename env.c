/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:21:57 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/23 19:46:30 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **env, char *key)
{
	int	i;

	if (!key || !*key)
		return (ft_strdup(""));
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
			return (env[i] + ft_strlen(key) + 1);
		i++;
	}
	return (ft_strdup(""));
}

void	set_env(char ***env, char *key, char *value)
{
	int	i;

	if (!key || !*key)
		return ;
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], key, ft_strlen(key)))
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin(ft_strjoin(key, "="), value);
			return ;
		}
		i++;
	}
	ft_vecadd(env, ft_strjoin(ft_strjoin(key, "="), value));
}

static char	*join_path(char *s1, char *s2)
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
	extern char	**environ;
	char		**v;
	char		*path;
	int			i;

	i = 0;
	v = ft_split(get_env(environ, "PATH"), ':');
	while (v[i])
	{
		path = join_path(v[i], program);
		if (!access(path, X_OK))
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	ft_vecfree(v);
	return (NULL);
}

void	ft_cd(char **vec, char ***env)
{
	int	j;

	if (!vec[1])
		j = chdir(get_env(*env, "HOME"));
	else if (!ft_strncmp(vec[1], "-", 1))
		j = chdir(get_env(*env, "OLD_PWD"));
	else
		j = chdir(vec[1]);
	if (j != 0)
		return (terminate("cd", "No such file or directory"));
	set_env(env, "OLD_PWD", get_env(*env, "PWD"));
	set_env(env, "PWD", getcwd(NULL, 0));
}
