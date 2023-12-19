/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:23:54 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/08 18:33:45 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_vecnjoin(char **v, char *sep, int n)
{
	char	*s;
	char	*tmp;
	int		i;

	i = 0;
	s = ft_strdup("");
	while (i < n)
	{
		tmp = s;
		s = ft_strjoin(s, v[i]);
		free(tmp);
		if (i + 1 < n)
		{
			tmp = s;
			s = ft_strjoin(s, sep);
			free(tmp);
		}
		i++;
	}
	return (s);
}
