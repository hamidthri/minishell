/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:49:12 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/23 19:32:14 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminate(char *cmd, char *reason)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (reason)
		ft_putstr_fd(reason, 2);
	else
		ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

char	*here_doc(char *end)
{
	char	*line;
	char	*str;
	char	*tmp;

	if (!end || !*end)
		return (terminate(NULL, ERR_HD), ft_strdup("ERR"));
	str = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strlen(line) == ft_strlen(end) && !ft_strncmp(line,
					end, ft_strlen(end))))
			return (free(line), str);
		tmp = str;
		str = ft_strjoin(str, ft_strjoin("\n", line));
		if (((*end == '"' || *end == '\'') && parse_quotes(line).end == *end))
			return (ft_substr(str, 0, ft_strchr(str, *end) - str));
		free(tmp);
		free(line);
	}
	return (str);
}

void	print_vec(char **vec)
{
	int	i;

	i = 0;
	while (vec[i])
	{
		ft_putstr_fd(vec[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

void	ft_echo(char **vec)
{
	int				i;
	int				flag;

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
		ft_putstr_fd(vec[i++], STDOUT_FILENO);
		if (vec[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	process(char *line, char **tokens, char ***env)
{
	int	i;

	i = -1;
	add_history(line);
	while (tokens[i++])
		tokens[i - 1] = parse(tokens[i - 1], *env);
	if (!ft_strncmp(line, "exit ", 5))
		ft_exit(tokens);
	run_pipes(tokens, ft_veclen(tokens), env);
	free(line);
	ft_vecfree(tokens);
	write_history("~/.minishell_history");
}
