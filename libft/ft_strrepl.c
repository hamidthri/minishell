/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:44:49 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/20 13:21:14 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrepl(char *src, char *old, char *new)
{
	char	*tmp;
	char	*spot;
	char	*res;

	spot = ft_strnstr(src, old, ft_strlen(src));
	if (!spot)
		return (ft_strdup(src));
	tmp = ft_calloc(ft_strlen(src) + (ft_strcount(src, old) * (ft_strlen(new)
					- ft_strlen(old))) + 1, sizeof(char));
	res = tmp;
	while (*src)
	{
		if (src != spot)
			*tmp++ = *src++;
		else
		{
			ft_strcpy(tmp, new);
			tmp += ft_strlen(new);
			src += ft_strlen(old);
			spot = ft_strnstr(src, old, ft_strlen(src));
		}
	}
	return (res);
}
