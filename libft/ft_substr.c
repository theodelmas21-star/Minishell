/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 10:16:39 by ssivilay          #+#    #+#             */
/*   Updated: 2026/01/21 14:41:23 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (!s || start >= ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	return (res);
}
