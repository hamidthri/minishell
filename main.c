/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:14:02 by mmomeni           #+#    #+#             */
/*   Updated: 2023/11/30 18:14:12 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char		*message;
	char		**token;
	t_builtin	*bltin;

	if (argc != 1)
	{
		printf("Error: This program takes no command-line arguments.\n");
		exit (0);
	}
	(void)argv;
	bltin = malloc(sizeof(t_builtin));
	bltin->env = env_dup(envp);
	// get_env(bltin->env);
	find_pwd(bltin);
	printf("pwd: %s\n", bltin->pwd);
	while (1)
	{
		message = readline("bash --> ");
		token = history_tokenize(message);
		if (token[0])
		{
			if (!ft_strncmp(token[0], "cd", 3))
			{
				cd_custom(bltin, "..");
				// printf("hallo cd\n");
			}
			else if (!ft_strncmp(token[0], "pwd", 3))
				printf("hallo pwd\n");
			else if (!ft_strncmp(token[0], "echo", 3))
				printf("hallo pwd\n");
			else if (!ft_strncmp(token[0], "export", 3))
				printf("hallo pwd\n");
			else if (!ft_strncmp(token[0], "unset", 3))
				printf("hallo pwd\n");
			else if (!ft_strncmp(token[0], "env", 3))
				get_env(envp);
		}
	}
}


// int	main(int argc, char **argv, char **envp)
// {
// 	char		*line;
// 	t_builtin	*builtin;

// 	if (argc != 1)
// 	{
// 		printf("Error: This program takes no command-line arguments.\n");
// 		exit (0);
// 	}

// 	builtin = malloc(sizeof(t_builtin));
// 	find_pwd(builtin, envp);
// 	line = get_next_line(STDIN_FILENO);
// 	while (line)
// 	{
// 		free(line);
// 		line = NULL;
// 	}
// }

