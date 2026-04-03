/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:31:31 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 14:34:25 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_free(char *str, char *str2, char *str_to_free)
{
	char	*new;
	t_index	idx;

	new = malloc(ft_strlen(str) + ft_strlen(str2) + 1);
	if (!new)
		return (free(str_to_free), NULL);
	idx = (t_index){0};
	if (str != NULL)
	{
		while (str[idx.i])
		{
			new[idx.i] = str[idx.i];
			idx.i++;
		}
	}
	while (str2[idx.j])
	{
		new[idx.i + idx.j] = str2[idx.j];
		idx.j++;
	}
	new[idx.i + idx.j] = '\0';
	if (str_to_free)
		free(str_to_free);
	return (new);
}

char	*ft_strjoin_free_both(char *str, char *str2)
{
	char	*new;
	t_index	idx;

	new = malloc(ft_strlen(str) + ft_strlen(str2) + 1);
	if (!new)
		return (free(str2), free(str), NULL);
	idx = (t_index){0};
	if (str != NULL && str[0] != '\0')
	{
		while (str[idx.i])
		{
			new[idx.i] = str[idx.i];
			idx.i++;
		}
	}
	while (str2[idx.j])
	{
		new[idx.i + idx.j] = str2[idx.j];
		idx.j++;
	}
	new[idx.i + idx.j] = '\0';
	if (str)
		free(str);
	return (free(str2), new);
}
