/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:24:06 by htaheri           #+#    #+#             */
/*   Updated: 2023/12/01 19:07:56 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_all_digit(char *str)
{
	int		i;

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
	int		code;

	if (!str)
		code = 0;
	else if (is_all_digit(str))
		code = ft_atoi(str);
	else
	{
		ft_putendl_fd("exit: ", STDERR_FILENO);
		ft_putendl_fd(str, STDERR_FILENO);
		ft_putendl_fd("Not a numeric argument", stderr);
		code = 255;
	}
	exit (code);
}

void	custom_exit(char **str)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_code(str[1]);
}
