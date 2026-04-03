/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 08:13:58 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 10:48:53 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	join_tab_first(char **cmd, char **new, int pos)
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

char	**join_split(int str, t_cmd *cmd)
{
	char	**tmp;
	t_index	index;
	char	**new;

	index = (t_index){0};
	if (ft_strchr(cmd->cmd[str], ' ') == NULL)
		return (cmd->cmd);
	tmp = ft_split(cmd->cmd[str], ' ');
	if (!tmp)
		return (NULL);
	if (str != 0 && cmd->cmd[str][0] == ' ' && cmd->sub_args[str
		- 1] == cmd->sub_args[str])
	{
		tmp = tab_space(tmp);
		if (!tmp)
			return (NULL);
	}
	index = size_index(cmd->cmd, tmp, str);
	new = malloc(sizeof(char *) * (index.i + index.j));
	if (!new)
		return (free_tab(tmp), NULL);
	new = join_tab(cmd->cmd, tmp, new, index.k);
	if (!new)
		return (free_tab(tmp), NULL);
	return (free_tab(tmp), free_tab(cmd->cmd), new);
}
