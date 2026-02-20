/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 10:44:41 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/01/27 11:34:42 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	checker(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

unsigned long	ft_strlen(char *str)
{
	unsigned long	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *str, char *str2)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(ft_strlen(str) + ft_strlen(str2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	}
	while (str2[j])
	{
		new[i + j] = str2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

char	*get_line(char *str)
{
	char			*new;
	unsigned long	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		new[i++] = '\n';
	new[i] = '\0';
	return (new);
}

char	*get_next(char *str)
{
	char			*new;
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	new = NULL;
	if (!str)
		return (NULL);
	while (str[j] != '\n' && str[j] != '\0')
		j++;
	if (str[j] == '\n' && str[j + 1] != '\0')
	{
		new = malloc((ft_strlen(str) - j) + 1);
		if (!new)
			return (NULL);
		while (str[++j] != '\0')
			new[i++] = str[j];
		new[i] = '\0';
	}
	return (new);
}
