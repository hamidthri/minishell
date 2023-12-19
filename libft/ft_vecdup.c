/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:46:04 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/11 15:46:24 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_vecdup(char **v)
{
	char	**dup;
	int		i;

	i = 0;
	while (v[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (v[i])
	{
		dup[i] = ft_strdup(v[i]);
		i++;
	}
	return (dup);
}
