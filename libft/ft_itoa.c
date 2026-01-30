/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 21:02:46 by ssivilay          #+#    #+#             */
/*   Updated: 2025/11/18 11:39:33 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nlen(int n)
{
	size_t	len;
	long	nb;

	len = 0;
	nb = (long)n;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	nb;
	size_t	nlen;

	nb = (long)n;
	nlen = ft_nlen(n);
	res = ft_calloc(sizeof(char), nlen + 1);
	if (!res)
		return (NULL);
	if (nb == 0)
	{
		res[0] = '0';
		return (res);
	}
	if (nb < 0)
	{
		res[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		res[--nlen] = (nb % 10) + '0';
		nb /= 10;
	}
	return (res);
}
