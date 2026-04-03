/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 15:01:53 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/03 15:19:35 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	init_cmd_fields(t_cmd *cmd)
{
	cmd->cmd[0] = NULL;
	cmd->is_expand[0] = 0;
	cmd->sub_args[0] = 0;
	cmd->quote_type[0] = 0;
	cmd->redirs = NULL;
	cmd->is_builtin = 0;
	cmd->pipefd[0] = -1;
	cmd->pipefd[1] = -1;
	cmd->cmd_error = 0;
}

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = malloc(sizeof(char *));
	cmd->is_expand = malloc(sizeof(int));
	cmd->sub_args = malloc(sizeof(int));
	cmd->quote_type = malloc(sizeof(int));
	if (!cmd->cmd || !cmd->is_expand || !cmd->sub_args || !cmd->quote_type)
	{
		free(cmd->cmd);
		free(cmd->is_expand);
		free(cmd->sub_args);
		free(cmd->quote_type);
		return (free(cmd), NULL);
	}
	init_cmd_fields(cmd);
	return (cmd);
}

int	get_expand_type(char *arg, t_quote quote_type)
{
	if (is_expandable(arg) && quote_type == DQUOTE)
		return (1);
	else if (is_expandable(arg) && quote_type != SQUOTE)
		return (2);
	return (0);
}

int	cmd_grow_malloc(t_cmd *cmd, int len)
{
	char	**new_cmd;
	int		*new_exp;
	int		*new_sub;
	int		*new_qt;

	new_cmd = malloc(sizeof(char *) * (len + 2));
	new_exp = malloc(sizeof(int) * (len + 2));
	new_sub = malloc(sizeof(int) * (len + 2));
	new_qt = malloc(sizeof(int) * (len + 2));
	if (!new_cmd || !new_exp || !new_sub || !new_qt)
		return (free(new_cmd), free(new_exp), free(new_sub), free(new_qt), 0);
	ft_memcpy(new_cmd, cmd->cmd, sizeof(char *) * len);
	ft_memcpy(new_exp, cmd->is_expand, sizeof(int) * len);
	ft_memcpy(new_sub, cmd->sub_args, sizeof(int) * len);
	ft_memcpy(new_qt, cmd->quote_type, sizeof(int) * len);
	free(cmd->cmd);
	free(cmd->is_expand);
	free(cmd->sub_args);
	free(cmd->quote_type);
	cmd->cmd = new_cmd;
	cmd->is_expand = new_exp;
	cmd->sub_args = new_sub;
	cmd->quote_type = new_qt;
	return (1);
}

int	cmd_add_arg(t_cmd *cmd, char *arg, t_quote qt, int is_new)
{
	int	len;

	len = 0;
	while (cmd->cmd[len])
		len++;
	if (!cmd_grow_malloc(cmd, len))
		return (0);
	cmd->cmd[len] = ft_strdup(arg);
	cmd->cmd[len + 1] = NULL;
	cmd->is_expand[len] = get_expand_type(arg, qt);
	cmd->is_expand[len + 1] = -1;
	cmd->quote_type[len] = qt;
	cmd->quote_type[len + 1] = -1;
	if (is_new && len > 0)
		cmd->sub_args[len] = cmd->sub_args[len - 1] + 1;
	else if (is_new && len == 0)
		cmd->sub_args[len] = len;
	else
		cmd->sub_args[len] = cmd->sub_args[len - 1];
	cmd->sub_args[len + 1] = -1;
	cmd->is_builtin = (is_builtin(cmd->cmd[0]) && !is_subarg(cmd->sub_args[0],
				cmd->sub_args[1]));
	return (1);
}
