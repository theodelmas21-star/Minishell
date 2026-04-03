/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:47:23 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 14:23:18 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_expand(t_cmd *cmd, int ind_cmd)
{
	t_index	index;

	index = (t_index){0};
	while (cmd->cmd[ind_cmd][index.i])
	{
		if (cmd->cmd[ind_cmd][index.i] == '$')
			return (index.i);
		index.i++;
	}
	return (-1);
}

int	len_new(char *str, int ind_str)
{
	int	i;

	i = 0;
	while (str[ind_str] && str[ind_str] != ' ')
	{
		i++;
		ind_str++;
	}
	return (i);
}

int	is_expandable(char *str)
{
	if (ft_strchr(str, '$'))
		return (1);
	return (0);
}
