/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:11:29 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/19 16:57:59 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_redirect(char **v, int i)
{
	if (ft_strlen(v[i]) == 1)
	{
		if (v[i][0] == '<')
		{
			if (open(v[i + 1], O_RDONLY) < 0)
				return (terminate(v[i + 1], NULL), 1);
			dup2(open(v[i + 1], O_RDONLY), 0);
		}
		else if (v[i][0] == '>')
			dup2(open(v[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644), 1);
		return (2);
	}
	else if (ft_strlen(v[i]) == 2 && !ft_strncmp(v[i], ">>", 2))
	{
		dup2(open(v[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644), 1);
		return (2);
	}
	return (0);
}

void	parse_env_vars(char **v, char **env)
{
	int		i;
	char	*tmp;
	char	*loc;
	char	*end;
	char	*key;

	i = 0;
	while (v[i])
	{
		loc = v[i];
		while (ft_strchr(loc, '$'))
		{
			loc = ft_strchr(loc, '$');
			end = loc + 1;
			while (ft_isalnum(*end) || *end == '_')
				end++;
			key = ft_substr(loc, 1, end - loc - 1);
			tmp = get_env(env, key);
			v[i] = ft_strrepl(v[i], ft_strjoin("$", key), tmp);
			free(key);
			loc = end;
		}
		i++;
	}
}

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
static int	parse_heredoc(char **v, int i)
{
	t_quote_parsed	p;
	int				hd_err;

	p = parse_quotes(v[i]);
	hd_err = 0;
	if (p.end)
		hd_err = here_doc((char[2]){p.end, 0}, p.hint);
	else if ((ft_strlen(v[i]) == 2 && !ft_strncmp(v[i], "<<", 2)))
		hd_err = here_doc(v[i + 1], "heredoc> ");
	else if (ft_strnstr(v[i], "<<", ft_strlen(v[i])))
		hd_err = here_doc(ft_strchr(v[i], '<') + 2, "heredoc> ");
	if (hd_err == -1)
		return (2);
	if (!hd_err)
		return (0);
	return (1);
}

char	*parse(char *s, char **env)
{
	int		in[2];
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	**v;

	in[0] = 0;
	v = ft_split(s, ' ');
	parse_env_vars(v, env);
	in[1] = ft_veclen(v);
	while (v[in[0]++])
		in[1] -= parse_heredoc(v, in[0] - 1) + parse_redirect(v, in[0] - 1);
	tmp = ft_vecnjoin(v, " ", in[1]);
	tmp2 = ft_strtrim(tmp, " ");
	tmp3 = ft_strrmchr(tmp2, "\\;\"'");
	dprintf(2, "tmp3: [%s]\n", tmp3);
	free(tmp);
	free(tmp2);
	ft_vecfree(v);
	return (tmp3);
}
