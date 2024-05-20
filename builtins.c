/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 18:49:21 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/24 19:55:54 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_valid(char **vec, int i, char **kv)
{
	int	j;

	j = 0;
	if (!kv[0] || !*kv[0] || ft_isdigit(kv[0][0]) || vec[i][0] == '=')
		return (1);
	while (kv[0][j])
		if (ft_strchr("|<>[],.:/{}/+^%#@!~=-?&*", kv[0][j++]))
			return (1);
	return (0);
}

void	ft_export(char **vec, char ***env)
{
	int		i;
	char	**kv;

	i = 1;
	while (vec[i])
	{
		kv = ft_split(vec[i], '=');
		if (!vec[i] || !*vec[i] || !*kv)
		{
			terminate("export", ft_strjoin(vec[i],
					": is not a valid identifier adsfads"));
			i++;
			continue ;
		}
		if (export_valid(vec, i, kv))
			terminate("export", ft_strjoin(vec[i],
					": is not a valid identifier"));
		if (ft_veclen(kv) == 2)
			set_env(env, kv[0], kv[1]);
		ft_vecfree(kv);
		i++;
	}
}

void	ft_echo(char **vec)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (vec[1])
	{
		while (vec[i] && (ft_strncmp(vec[i], "-n", 2) == 0
				&& ft_strlen(vec[i]) == 2))
		{
			flag = 1;
			i++;
		}
	}
	while (vec[i])
	{
		ft_putstr_fd(vec[i++], 1);
		if (vec[i])
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
}

void	ft_exit(char **v)
{
	int	code;

	ft_putendl_fd("exit", 1);
	if (!v[0])
		code = 0;
	else if (ft_strisnum(v[0] + 4))
		code = ft_atoi(v[0] + 4);
	else
		code = 255;
	exit(code);
}
