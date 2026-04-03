/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_rest_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:54:37 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 15:18:21 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_rest(char **rest, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(rest[i++]);
	free(rest);
}

char	**fill_rest_new(char **rest, char **new, t_index *index)
{
	while (new[index->j])
	{
		rest[index->j] = ft_strdup(new[index->j]);
		if (!rest[index->j])
			return (free_rest(rest, index->j), NULL);
		index->j++;
	}
	return (rest);
}

char	**fill_rest_cmd(char **rest, char **cmd, t_index *index, int len)
{
	while (cmd[index->k + len + 1])
	{
		rest[index->j] = ft_strdup(cmd[index->k + len + 1]);
		if (!rest[index->j])
			return (free_rest(rest, index->j), NULL);
		index->j++;
		index->k++;
	}
	rest[index->j] = NULL;
	return (rest);
}

char	**rest_cmd(char **cmd, int len, char **new, char **old)
{
	char	**rest;
	t_index	index;

	index = (t_index){0};
	index.i = len + 1;
	while (cmd[index.i])
		index.i++;
	rest = malloc(sizeof(char *) * index.i);
	if (!rest)
		return (NULL);
	if (!fill_rest_new(rest, new, &index))
		return (NULL);
	if (!fill_rest_cmd(rest, cmd, &index, len))
		return (NULL);
	free_tab_rest_cmd(old, index.i);
	return (rest);
}
