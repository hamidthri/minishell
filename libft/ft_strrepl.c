/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 20:44:49 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/14 22:25:38 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrepl(char *src, char *old, char *new)
{
	char	*tmp;
	char	*spot;
	int		wlen;
	char	*res;

	wlen = ft_strlen(old);
	spot = ft_strnstr(src, old, ft_strlen(src));
	if (!spot)
		return (ft_strdup(src));
	tmp = ft_calloc(ft_strlen(src) + (ft_strlen(new) - wlen) + 1, sizeof(char));
	res = tmp;
	while (*src)
	{
		if (src != spot)
			*tmp++ = *src++;
		else
		{
			while (*new)
				*tmp++ = *new ++;
			src += wlen;
		}
	}
	return (res);
}
