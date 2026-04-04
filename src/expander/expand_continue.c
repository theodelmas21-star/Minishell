/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 08:13:58 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/04 19:40:06 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**join_split(int str, t_cmd *cmd)
{
	char	**tmp;
	t_index	index;
	char	**new;
	char	**old;

	index = (t_index){0};
	if (ft_strchr(cmd->cmd[str], ' ') == NULL)
		return (cmd->cmd);
	tmp = ft_split(cmd->cmd[str], ' ');
	if (!tmp)
		return (NULL);
	if (str != 0 && cmd->cmd[str][0] == ' ' && cmd->sub_args[str
		- 1] == cmd->sub_args[str])
	{
		old = tmp;
		tmp = tab_space(tmp);
		free(old);
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
