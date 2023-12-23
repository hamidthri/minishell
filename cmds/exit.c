/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:24:06 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/23 19:19:50 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_all_digit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_code(char *str)
{
	int	code;

	if (!str)
		code = 0;
	else if (is_all_digit(str + 4))
		code = ft_atoi(str + 4);
	else
		code = 255;
	exit(code);
}

void	ft_exit(char **vec)
{
	ft_putendl_fd("exit", 1);
	exit_code(vec[0]);
}
