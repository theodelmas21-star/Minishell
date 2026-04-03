/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:41:43 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 15:18:05 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_expand(t_cmd *cmd, t_env *s_env, int exit_code,
		t_index *index)
{
	if (cmd->cmd[index->i + 1] && ft_strncmp("$", cmd->cmd[index->i],
			ft_strlen(cmd->cmd[index->i])) == 0
		&& cmd->sub_args[index->i] == cmd->sub_args[index->i + 1]
		&& cmd->quote_type[index->i] != 2)
	{
		free(cmd->cmd[index->i]);
		cmd->cmd[index->i] = NULL;
	}
	else
	{
		cmd->cmd[index->i] = expand_all(cmd, s_env, exit_code, index->i);
		if (!cmd->cmd[index->i] && cmd->quote_type[index->i] == 2)
			return (1);
	}
	return (0);
}

int	handle_split(t_cmd *cmd, t_index *index)
{
	index->j = index->i;
	index->k = count_words(cmd->cmd[index->i], ' ');
	cmd->cmd = join_split(index->j, cmd);
	if (!cmd->cmd)
		return (1);
	index->i += index->k;
	if (adapt_data(index->j, index->k, cmd) == 1)
		return (1);
	return (0);
}

int	handle_null(t_cmd *cmd, t_index *index)
{
	cmd->cmd = without_null(cmd->cmd, index->i);
	if (!cmd->cmd)
		return (1);
	adapt_data_null(index->i, cmd);
	return (0);
}

int	expand_cmd(t_cmd *cmd, t_env *s_env, int exit_code)
{
	t_index	index;

	index = (t_index){0};
	while (cmd->cmd[index.i])
	{
		if (is_expandable(cmd->cmd[index.i]) && cmd->is_expand[index.i] > 0)
			if (handle_expand(cmd, s_env, exit_code, &index))
				return (1);
		if (cmd->cmd[index.i] && cmd->cmd[index.i][0] != '\0'
			&& cmd->is_expand[index.i] == 2)
		{
			if (handle_split(cmd, &index))
				return (1);
			continue ;
		}
		if (cmd->cmd[index.i] == NULL)
		{
			if (handle_null(cmd, &index))
				return (1);
		}
		else
			index.i++;
	}
	return (0);
}
