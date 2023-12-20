/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:14:02 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/20 15:49:36 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	h_up(int count, int key)
{
	HIST_ENTRY	*entry;

	(void)count;
	(void)key;
	entry = previous_history();
	if (entry)
	{
		rl_replace_line(entry->line, 0);
		rl_point = rl_end;
		rl_redisplay();
	}
	return (0);
}

int	h_down(int count, int key)
{
	HIST_ENTRY	*entry;

	(void)count;
	(void)key;
	entry = next_history();
	if (entry)
		rl_replace_line(entry->line, 0);
	else
		rl_replace_line("", 0);
	rl_point = rl_end;
	rl_redisplay();
	return (0);
}

void	disable_ctrl_sign(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(0, TCSANOW, &term);
}

void	handle_ctrl_c(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	main(void)
{
	char		*line;
	char		**tokens;
	extern char	**environ;

	using_history();
	rl_bind_keyseq("\\e[A", &h_up);
	rl_bind_keyseq("\\e[B", &h_down);
	disable_ctrl_sign();
	signal(SIGINT, handle_ctrl_c);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (!*line)
			continue ;
		tokens = ft_split(line, '|');
		process(line, tokens, ft_vecdup(environ));
	}
	return (0);
}
