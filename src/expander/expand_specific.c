/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specific.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:34:50 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 21:14:01 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_sub_args(t_cmd *cmd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (cmd->cmd[i])
	{
		count++;
		while (cmd->cmd[i + 1] && cmd->sub_args[i] == cmd->sub_args[i + 1])
			i++;
		i++;
	}
	return (count);
}

char	*join_sub_args_new(t_cmd *cmd, t_index *index)
{
	char	*new;

	index->j = index->i + 1;
	new = ft_strdup(cmd->cmd[index->i]);
	if (!new)
		return (NULL);
	while (cmd->cmd[index->j]
		&& cmd->sub_args[index->i] == cmd->sub_args[index->j])
	{
		new = ft_strjoin_free(new, cmd->cmd[index->j], new);
		if (!new)
			return (NULL);
		index->j++;
	}
	return (new);
}

char	**join_sub_args(t_cmd *cmd)
{
	t_index	index;
	int		size;
	char	*new;
	char	**res;

	index = (t_index){0, 1, 0};
	if (!cmd || !cmd->sub_args)
		return (cmd->cmd);
	size = size_sub_args(cmd);
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	while (cmd->cmd[index.i] && index.k < size)
	{
		new = join_sub_args_new(cmd, &index);
		if (!new)
			return (free(res), NULL);
		res[index.k++] = new;
		index.i = index.j;
	}
	res[size] = NULL;
	free_tab(cmd->cmd);
	return (res);
}

char	**alloc_without_null(char **cmd, int len)
{
	t_index	index;
	char	**new;

	index = (t_index){0};
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	while (cmd[index.j])
	{
		new[index.k] = ft_strdup(cmd[index.j]);
		if (!new[index.k])
		{
			while (index.i < index.k)
				free(new[index.i++]);
			return (free(new), NULL);
		}
		index.j++;
		index.k++;
	}
	new[index.k] = NULL;
	return (new);
}

char	**without_null(char **cmd, int len)
{
	char	**new;
	char	**res;

	new = alloc_without_null(cmd, len);
	if (!new)
		return (NULL);
	res = rest_cmd(cmd, len, new, cmd);
	if (!res)
		return (free_tab(new), NULL);
	free_tab(new);
	return (res);
}
