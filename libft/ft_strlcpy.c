/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:10:19 by ssivilay          #+#    #+#             */
/*   Updated: 2025/11/11 10:13:34 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	if (siz > 0)
	{
		while (src[i] != '\0' && i < siz - 1)
		{
			dst[i] = src[i];
			i++;
		}
	}
	if (siz != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}
