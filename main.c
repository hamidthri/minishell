/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:14:02 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/02 19:37:18 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
    char * line;
    int fd[2];

    line = get_next_line(STDIN_FILENO);
    while (line)
    {
        run_pipes(fd, argv, argc);
        free(line);
        line = NULL;
    }
}
