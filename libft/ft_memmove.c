/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:15:12 by ssivilay          #+#    #+#             */
/*   Updated: 2025/11/12 14:20:01 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	if (!src && !dest)
		return (NULL);
	i = 0;
	dest_ptr = (unsigned char *)dest;
	src_ptr = (unsigned char *)src;
	if (dest_ptr > src_ptr)
	{
		while (n-- > 0)
			dest_ptr[n] = src_ptr[n];
	}
	else if (dest_ptr < src_ptr)
	{
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dest_ptr);
}
