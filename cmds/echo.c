/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:28:36 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/19 18:05:37 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_custom(char **str)
{
	int				i;
	int				flag;

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
	while (str[i])
	{
		ft_putstr_fd(str[i++], STDOUT_FILENO);
		if (str[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}
