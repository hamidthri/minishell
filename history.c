/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:11:14 by mmomeni           #+#    #+#             */
/*   Updated: 2023/11/15 16:32:05 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	history_add(char *cmd)
{
	int		fd;
	size_t	i;

    i = 0;
	fd = open("~/.minishell_history", O_CREAT | O_APPEND);
	while (cmd[i])
		i++;
	write(fd, "\n", 1);
	write(fd, cmd, i);
}
