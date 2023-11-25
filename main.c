/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:14:02 by mmomeni           #+#    #+#             */
/*   Updated: 2023/11/25 17:14:21 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_builtin	*builtin;

	if (argc != 1)
	{
		printf("Error: This program takes no command-line arguments.\n");
		exit (0);
	}

	builtin = malloc(sizeof(t_builtin));
	find_pwd(builtin, envp);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		free(line);
		line = NULL;
	}
}
