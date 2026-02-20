/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:31:31 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/20 10:23:24 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_free(char *str, char *str2, char *str_to_free)
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
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	while (str2[j])
	{
		new[i + j] = str2[j];
		j++;
	}
	new[i + j] = '\0';
	return (free(str_to_free), new);
}

char	*ft_strjoin_free_both(char *str, char *str2)
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
		while (str[i])
		{
			new[i] = str[i];
			i++;
		}
	while (str2[j])
	{
		new[i + j] = str2[j];
		j++;
	}
	new[i + j] = '\0';
	return (free(str2), free(str), new);
}
