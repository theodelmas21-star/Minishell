/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:50:29 by ssivilay          #+#    #+#             */
/*   Updated: 2025/11/12 14:20:20 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	ch;

	i = ft_strlen(s);
	str = (char *)s;
	ch = (unsigned char)c;
	while (i >= 0 && (unsigned char)str[i] != ch)
		i--;
	if ((unsigned char)str[i] == ch)
		return (&str[i]);
	return (NULL);
}
