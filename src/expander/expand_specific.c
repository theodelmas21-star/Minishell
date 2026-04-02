/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specific.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:34:50 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/02 18:00:21 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_number(char *new)
{
	char	*res;
	t_index	index;

	index = (t_index){0};
	while (new[index.i] && new[index.i] != ' ')
		index.i++;
	res = malloc(sizeof(char) * (index.i - 1));
	if (!res)
		return (NULL);
	while (new[index.j])
	{
		if (new[index.j] == '$' && new[index.j + 1] >= '0' && new[index.j
			+ 1] <= '9')
			index.j += 2;
		res[index.k] = new[index.j];
		index.j++;
		index.k++;
	}
	res[index.k] = '\0';
	return (free(new), res);
}

int size_sub_args(t_cmd *cmd)
{
    int i;
    int count;

	count = 0;
	i = 0;
    while (cmd->cmd[i])
    {
        count++;

        while (cmd->cmd[i + 1] &&
               cmd->sub_args[i] == cmd->sub_args[i + 1])
            i++;
        i++;
    }
    return (count);
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
		index.j = index.i + 1;
		new = ft_strdup(cmd->cmd[index.i]);
		if (!new)
			return (free(res), NULL);
		while (cmd->cmd[index.j] && cmd->sub_args[index.i] == cmd->sub_args[index.j])
		{
			new = ft_strjoin_free(new, cmd->cmd[index.j], new);
			if (!new)
				return (free(res), NULL);
			index.j++;
		}
		res[index.k] = new;
		index.k++;
		index.i = index.j;
	}
	res[size] = NULL;
	free_tab(cmd->cmd);
	return (res);
}

char **rest_cmd(char **cmd, int len, char **new, char **old)
{
	char **rest;
	t_index	index;
	int m;
	
	index = (t_index){0};
	index.i = len + 1;
	m = 0;
	while (cmd[index.i])
		index.i++;
	rest = malloc(sizeof(char *) * index.i);
	if (!rest)
		return NULL;
	while (new[index.j])
	{
		rest[index.j] = ft_strdup(new[index.j]);
		if (!rest[index.j])
		{
			while (m < index.j)
			{
				free(rest[m]);
				m++;
			}
			return (free(rest), NULL);
		}
		index.j++;
	}
	while (cmd[index.k + len + 1])
	{
		rest[index.j] = ft_strdup(cmd[index.k + len + 1]);
		if (!rest[index.j])
		{
			while (m < index.j)
			{
				free(rest[m]);
				m++;
			}
			free(rest);
			return (free(rest), NULL);
		}
		index.j++;
		index.k++;
	}
	rest[index.j] = NULL;
	free_tab_rest_cmd(old, index.i);
	return (rest);
}

char	**without_null(char **cmd, int len)
{
	t_index	index;
	char	**new;
	char 	**res;

	index = (t_index){0};
	new = malloc(sizeof(char *) * (len + 1));
	if (!new)
		return (NULL);
	while (cmd[index.j])
	{
		new[index.k] = ft_strdup(cmd[index.j]);
		if (!new[index.k])
		{
			int m = 0;
			while (m < index.k)
			{
				free(new[m]);
				m++;
			}
			free(new);
			return NULL;
		}
		index.j++;
		index.k++;
	}
	new[index.k] = NULL;
	res = rest_cmd(cmd, len, new, cmd);
	if (!res)
	{
		free_tab(new);
		return NULL;
	}
	free_tab(new);
	return (res);
}
