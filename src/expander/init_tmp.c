/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:01:47 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 11:03:18 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*r_newline(char *res)
{
	t_index	index;
	char	*new;

	index = (t_index){0};
	new = malloc(sizeof(char) * (ft_strlen(res) + 1));
	if (!new)
		return (free(res), NULL);
	while (res[index.i] && res[index.i] != '\n')
	{
		new[index.i] = res[index.i];
		index.i++;
	}
	new[index.i] = '\0';
	return (free(res), new);
}

int	init_tmp_arrays(t_cmd *tmp)
{
	tmp->is_expand = malloc(sizeof(int) * 1);
	if (!tmp->is_expand)
		return (free(tmp), free_tab(tmp->cmd), 0);
	tmp->is_expand[0] = 1;
	tmp->quote_type = malloc(sizeof(int) * 1);
	if (!tmp->quote_type)
		return (free(tmp), free_tab(tmp->cmd), free(tmp->is_expand), 0);
	tmp->quote_type[0] = 2;
	tmp->sub_args = malloc(sizeof(int) * 1);
	if (!tmp->sub_args)
		return (free(tmp), free_tab(tmp->cmd), free(tmp->is_expand),
			free(tmp->quote_type), 0);
	tmp->sub_args[0] = 1;
	return (1);
}

t_cmd	*init_tmp(char *res)
{
	t_cmd	*tmp;

	res = r_newline(res);
	if (!res)
		return (NULL);
	tmp = malloc(sizeof(t_cmd));
	if (!tmp)
		return (NULL);
	tmp->cmd = malloc(sizeof(char *) * 2);
	if (!tmp->cmd)
		return (free(tmp), NULL);
	tmp->cmd[0] = res;
	tmp->cmd[1] = NULL;
	if (!init_tmp_arrays(tmp))
		return (NULL);
	return (tmp);
}
