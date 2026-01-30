/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:50:52 by ssivilay          #+#    #+#             */
/*   Updated: 2025/11/18 13:41:40 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd((n / 10), fd);
	ft_putchar_fd(('0' + (n % 10)), fd);
}
