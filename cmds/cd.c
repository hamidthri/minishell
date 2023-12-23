/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:22:12 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/23 03:36:22 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	new_path(char ***env)
{
	set_env(env, "OLD_PWD", get_env(*env, "PWD"));
	set_env(env, "PWD", getcwd(NULL, 0));
}

int	find_dir(char ***env, char *s)
{
	char	*dir;
	int		i;
	int		j;

	dir = NULL;
	i = 0;
	while ((*env)[i])
	{
		if (!ft_strncmp((*env)[i], s, ft_strlen(s)))
		{
			dir = ft_strdup((*env)[i] + ft_strlen(s));
			break ;
		}
		i++;
	}
	if (dir == NULL)
		return (terminate(s, "not found"), -1);
	j = chdir(dir);
	if (j != 0)
		perror("chdir failed");
	free(dir);
	return (j);
}

void	ft_cd(char **vec, char ***env)
{
	int	j;

	if (!vec[1])
		j = find_dir(env, "HOME=");
	else if (!ft_strncmp(vec[1], "-", 1))
		j = find_dir(env, "OLDPWD=");
	else
	{
		j = chdir(vec[1]);
		if (j != 0)
			terminate("cd", "No such file or directory");
	}
	if (j != 0)
		return ;
	new_path(env);
}
