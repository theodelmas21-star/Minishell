/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_continue_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:23:17 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/04 19:27:04 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**tab_space(char **tmp)
{
	char	**new;
	t_index	index;

	index = (t_index){0};
	while (tmp[index.j])
		index.j++;
	new = malloc(sizeof(char *) * (index.j + 2));
	if (!new)
		return (free_tab(tmp), NULL);
	new[0] = ft_strdup("\0");
	while (tmp[index.i])
	{
		new[index.i + 1] = tmp[index.i];
		index.i++;
	}
	new[index.i + 1] = NULL;
	return (new);
}

t_index	size_index(char **cmd, char **tmp, int str)
{
	t_index	index;

	index = (t_index){0};
	while (cmd[index.i])
		index.i++;
	while (tmp[index.j])
		index.j++;
	while (cmd[index.k] != cmd[str])
		index.k++;
	return (index);
}

int	join_tab_first(char **cmd, char **new, int pos)
{
	t_index	index;

	index = (t_index){0};
	while (index.i < pos)
	{
		new[index.i] = ft_strdup(cmd[index.i]);
		if (!new[index.i])
			return (0);
		index.i++;
	}
	return (1);
}

char	**join_tab(char **cmd, char **tmp, char **new, int pos)
{
	t_index	index;

	index = (t_index){0};
	if (!join_tab_first(cmd, new, pos))
		return (NULL);
	index.i = pos;
	while (tmp[index.j])
	{
		new[index.i] = ft_strdup(tmp[index.j]);
		if (!new[index.i])
			return (NULL);
		index.i++;
		index.j++;
	}
	index.k = pos + 1;
	while (cmd[index.k])
	{
		new[index.i] = ft_strdup(cmd[index.k]);
		if (!new[index.i])
			return (NULL);
		index.i++;
		index.k++;
	}
	new[index.i] = NULL;
	return (new);
}
