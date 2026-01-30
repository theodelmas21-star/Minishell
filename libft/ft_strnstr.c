/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:50:00 by ssivilay          #+#    #+#             */
/*   Updated: 2025/11/11 16:16:19 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*big_ptr;

	big_ptr = (char *)big;
	if (little[0] == '\0')
		return (big_ptr);
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		while (little[j] == big[i + j] && i + j < len)
		{
			if (little[j + 1] == 0)
				return (&big_ptr[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
