/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:56:23 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/15 16:58:55 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vecadd(char ***vec, char *str)
{
	int		i;
	char	**new_vec;

	i = ft_veclen(*vec);
	new_vec = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while ((*vec)[i])
	{
		new_vec[i] = ft_strdup((*vec)[i]);
		i++;
	}
	new_vec[i] = ft_strdup(str);
	new_vec[i + 1] = NULL;
	free(*vec);
	*vec = new_vec;
}
