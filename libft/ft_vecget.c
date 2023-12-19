/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:49:38 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/19 18:02:51 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_vecget(char **vec, char *key)
{
	int i;

	i = 0;
	while (vec[i])
	{
		if (!ft_strcmp(vec[i], key))
			return (vec[i]);
		i++;
	}
	return (NULL);
}
