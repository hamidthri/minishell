/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:49:12 by htaheri           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/20 15:51:52 by mmomeni          ###   ########.fr       */
=======
/*   Updated: 2023/12/19 18:15:53 by htaheri          ###   ########.fr       */
>>>>>>> 088592e997c0706f8ca5a8f4f2a3789984a745ac
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
<<<<<<< HEAD
		return (terminate(NULL, HD_ERR), ft_strdup("ERR"));
	str = ft_strdup("");
=======
		return (terminate(NULL, "syntax error near unexpected token `newline'"),
			-1);
	tmp_file = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
>>>>>>> 088592e997c0706f8ca5a8f4f2a3789984a745ac
	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strlen(line) == ft_strlen(end) && !ft_strncmp(line,
					end, ft_strlen(end))) || ((*end == '"' || *end == '\'')
					&& parse_quotes(line).end == *end))
			return (free(line), str);
		tmp = str;
		str = ft_strjoin(str, ft_strjoin("\n", line));
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
		printf("[%s] ", vec[i]);
		i++;
	}
	printf("\n");
}
<<<<<<< HEAD

void	process(char *line, char **tokens, char **environ)
{
	int	i;

	i = 0;
	add_history(line);
	while (tokens[i++])
		tokens[i - 1] = parse(tokens[i - 1], ft_vecdup(environ));
	run_pipes((int[2]){1, 2}, tokens, ft_veclen(tokens), environ);
	free(line);
	ft_vecfree(tokens);
	write_history("~/.minishell_history");
}
=======
>>>>>>> 088592e997c0706f8ca5a8f4f2a3789984a745ac
