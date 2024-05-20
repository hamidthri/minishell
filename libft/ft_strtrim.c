/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 08:53:34 by mmomeni           #+#    #+#             */
/*   Updated: 2023/12/23 17:23:36 by mmomeni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isin(char c, char const *s)
{
	size_t	sl;

	sl = ft_strlen(s);
	while (sl--)
		if (s[sl] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (!s1 || !set)
		return (NULL);
	if (!*s1 || !*set)
		return (ft_strdup(s1));
	start = 0;
	while (ft_isin(s1[start], set))
		start++;
	if (start == (int)ft_strlen(s1))
		return (ft_strdup(""));
	end = (ft_strlen(s1) - 1);
	while (ft_isin(s1[end], set))
		end--;
	return (ft_substr(s1, start, (end - start) + 1));
}
