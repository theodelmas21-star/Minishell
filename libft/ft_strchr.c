/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:03:42 by ssivilay          #+#    #+#             */
/*   Updated: 2025/11/19 12:00:15 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	ch;

	i = 0;
	str = (char *)s;
	ch = (unsigned char)c;
	while (str[i] != '\0' && (unsigned char)str[i] != ch)
		i++;
	if ((unsigned char)str[i] == ch)
		return (&str[i]);
	return (NULL);
}
