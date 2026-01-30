/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 10:21:48 by ssivilay          #+#    #+#             */
/*   Updated: 2025/11/11 17:14:19 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_ptr;
	unsigned char	*dest_ptr;

	i = 0;
	src_ptr = (unsigned char *)src;
	dest_ptr = (unsigned char *)dest;
	if (!src && !dest)
		return (NULL);
	while (i < n)
	{
		dest_ptr[i] = src_ptr[i];
		i++;
	}
	return (dest);
}
