/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:28:36 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/19 17:08:48 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*r_quotes(char *str, int c)
// {
// 	char	**split_str;
// 	char	*new_str;
// 	int		i;

// 	i = 0;
// 	split_str = ft_split(str, c);
// 	while (split_str[0][i])
// 		i++;
// 	new_str = ft_calloc(i + 1, sizeof(char));
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	while (split_str[0][i])
// 	{
// 		new_str[i] = split_str[0][i];
// 		i++;
// 	}
// 	free_all(split_str);
// 	return (new_str);
// }

// int	needs_quote(char *input, int c)
// {
// 	int	q;

// 	q = 0;
// 	while (*input)
// 	{
// 		if (*input == c)
// 			q++;
// 		input++;
// 	}
// 	return (q % 2 != 0);
// }

// char	*r_quotes(char *str, int c)
// {
// 	char	*new_str;
// 	int		i;
// 	int		j;

// 	new_str = ft_calloc(strlen(str) + 1, sizeof(char));
// 	if (!new_str)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] != c)
// 			new_str[j++] = str[i];
// 		i++;
// 	}
// 	return (new_str);
// }

// char	*r_quotes(char *str, char c)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == c)
// 		{
// 			j = 0;
// 			while (str[i + j] == c)
// 				j++;
// 			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
// 		}
// 		i++;
// 	}
// 	return (str);
// }

// char	*handle_quotes(char *str)
// {
// 	char	*m_str;

// 	if (ft_strchr(str, '\"'))
// 	{
// 		m_str = r_quotes(str, '\"');
// 		// if (needs_quote(str, '\"'))
// 		// 	here_doc("\"");
// 	}
// 	else if (ft_strchr(str, '\''))
// 	{
// 		m_str = r_quotes(str, '\'');
// 		// if (needs_quote(str, '\''))
// 		// 	here_doc("\'");
// 	}
// 	else
// 		m_str = str;
// 	return (m_str);
// }

// static char	*parse_quotes(const char *s)
// {
// 	char	*result;
// 	int		ij[2];
// 	int		quote;

// 	result = ft_calloc(strlen(s) + 1, sizeof(char));
// 	ij[0] = -1;
// 	ij[1] = 0;
// 	quote = 0;
// 	while (s[++ij[0]])
// 	{
// 		if (s[ij[0]] == '\'' || s[ij[0]] == '"')
// 		{
// 			if (quote == 0)
// 				quote = s[ij[0]];
// 			else if (quote == s[ij[0]])
// 				quote = 0;
// 			else
// 				result[ij[1]++] = s[ij[0]];
// 		}
// 		else
// 			result[ij[1]++] = s[ij[0]];
// 	}
// 	if (quote != 0)
// 		return (free(result), NULL);
// 	return (result);
// }

// typedef struct s_quote_parsed
// {
// 	char		*str;
// 	char		end;
// 	char		*hint;
// }				t_quote_parsed;

t_quote_parsed	parse_quotes(const char *s)
{
	t_quote_parsed	p;
	int				ij[2];

	ij[0] = -1;
	ij[1] = 0;
	p.str = ft_calloc(strlen(s) + 1, sizeof(char));
	p.end = 0;
	p.hint = ft_strdup("quote> ");
	while (s[++ij[0]])
	{
		if (s[ij[0]] == '\'' || s[ij[0]] == '"')
		{
			if (p.end == 0)
				p.end = s[ij[0]];
			else if (p.end == s[ij[0]])
				p.end = 0;
			else
				p.str[ij[1]++] = s[ij[0]];
		}
		else
			p.str[ij[1]++] = s[ij[0]];
	}
	if (p.end == '"')
		p.hint = ft_strdup("dquote> ");
	return (p);
}

// void	here_doc(char c)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("temp", O_WRONLY | O_CREAT, 0644);
// 	while (1)
// 	{
// 		line = get_next_line(STDIN_FILENO);
// 		// printf("%s\n", line);
// 		if (ft_strncmp(line, &c, 1) == 0)
// 		{
// 			free(line);
// 			return ;
// 		}
// 		ft_putstr_fd(line, fd);
// 		free(line);
// 	}
// }

void	here_doc(char *end, char *hint)
{
	char	*line;
	int		tmp_file;

	// if (!end || !*end)
	//     return (terminate(NULL,
	//                         "syntax error near unexpected token `newline'"),
	//             -1);
	printf("end: %s\n", end);
	tmp_file = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		line = readline(hint);
		if (!line || (ft_strlen(line) == ft_strlen(end) && !ft_strncmp(line,
					end, ft_strlen(end))))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, tmp_file);
		free(line);
		line = NULL;
	}
	// dup2(tmp_file, 0);
	// close(tmp_file);
	// return (tmp_file);
}

void	echo_custom(char **str)
{
	int				i;
	int				flag;
	int				f_des;
	t_quote_parsed	q;
	char			*line;
	char			*map_str;

	map_str = ft_calloc(1, 1);
	i = 1;
	flag = 0;
	if (str[1])
	{
		while (str[i] && (ft_strncmp(str[i], "-n", 2) == 0
				&& ft_strlen(str[i]) == 2))
		{
			flag = 1;
			i++;
		}
	}
	q = parse_quotes(str[1]);
	if (q.end)
	{
		here_doc(&q.end, q.hint);
		f_des = open("tmp", O_RDONLY);
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
		ft_putstr_fd(q.str, STDOUT_FILENO);
		ft_putstr_fd(map_str, 1);
		if (!flag)
			ft_putstr_fd("\n", STDOUT_FILENO);
		free(map_str);
	}
	else
	{
		ft_putstr_fd(q.str, STDOUT_FILENO);
	}
}
