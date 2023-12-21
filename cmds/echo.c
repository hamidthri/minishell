/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:28:36 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/21 19:18:48 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
