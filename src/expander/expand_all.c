/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:36:03 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 11:39:29 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_expandable_dollar(char *str, int i)
{
	char	next;

	if (str[i] != '$')
		return (0);
	next = str[i + 1];
	if (!next || next == ' ' || next == '=' || next == ':')
		return (0);
	if (next == '%' || next == '\'')
		return (0);
	return (1);
}

char	*expand_dollar_type(char *new, t_env *s_env, int exit_code,
		t_index *index)
{
	if (new[1] == '?' && new[2] == '\0')
		new = interrogation(new, exit_code);
	else if (is_env(new, s_env) >= 0)
		new = call_exp_env(new, s_env);
	else if (new[1] >= '0' && new[1] <= '9')
		new = handle_number(new);
	else
	{
		free(new);
		new = ft_strdup("");
		index->k = 1;
	}
	return (new);
}

char	*expand_dollar(t_cmd *cmd, t_env *s_env, int exit_code,
		t_index *index, int str)
{
	char	*new;
	int		to_replace;

	new = create_new(cmd->cmd[str], index->i);
	if (!new)
		return (NULL);
	to_replace = ft_strlen(new);
	new = expand_dollar_type(new, s_env, exit_code, index);
	if (!new)
		return (NULL);
	index->j = ft_strlen(new);
	new = return_new(cmd->cmd[str], new, to_replace, index->i);
	if (!new)
		return (NULL);
	cmd->cmd[str] = new;
	index->i += index->j - 1;
	return (new);
}

char	*expand_lone_dollar(t_cmd *cmd, t_index *index, int str)
{
	char	*new;

	new = ft_strdup("");
	index->k = 1;
	index->j = ft_strlen(new);
	new = return_new(cmd->cmd[str], new, 1, index->i);
	if (!new)
		return (NULL);
	cmd->cmd[str] = new;
	index->i += index->j - 1;
	return (new);
}

char	*expand_all(t_cmd *cmd, t_env *s_env, int exit_code, int str)
{
	t_index	index;

	index = (t_index){0};
	while (cmd->cmd[str][index.i])
	{
		if (is_expandable_dollar(cmd->cmd[str], index.i))
		{
			if (!expand_dollar(cmd, s_env, exit_code, &index, str))
				return (NULL);
		}
		else if (cmd->cmd[str][index.i] == '$' && !cmd->cmd[str][index.i + 1]
			&& cmd->quote_type[str + 1] == 2)
		{
			if (!expand_lone_dollar(cmd, &index, str))
				return (NULL);
		}
		index.i++;
	}
	if (index.k == 1 && cmd->cmd[str][0] == '\0' && cmd->quote_type[str] != 2)
		return (free(cmd->cmd[str]), NULL);
	return (cmd->cmd[str]);
}
