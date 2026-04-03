/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:39:21 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/03 16:55:36 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab_rest_cmd(char **old, int len)
{
	int	i;

	if (!old)
		return ;
	i = 0;
	while (i < len)
	{
		free(old[i]);
		i++;
	}
	free(old);
}

void	free_redir(void *content)
{
	t_redir	*redir;

	redir = (t_redir *)content;
	if (!redir)
		return ;
	if (redir->target != NULL)
		free(redir->target);
	if (redir->delimiter != NULL)
		free(redir->delimiter);
	free(redir);
}

void	free_tab_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->cmd)
		return ;
	while (cmd->is_expand[i] != -1)
	{
		free(cmd->cmd[i]);
		i++;
	}
	free(cmd->cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_tab_cmd(cmd);
	free(cmd->is_expand);
	free(cmd->sub_args);
	free(cmd->quote_type);
	if (cmd->redirs)
		ft_lstclear(&cmd->redirs, free_redir);
	free(cmd);
}

void	free_cmds(t_list *cmds)
{
	t_list	*current;
	t_cmd	*cur_cmd;

	if (!cmds)
		return ;
	while (cmds)
	{
		current = cmds;
		cur_cmd = (t_cmd *)current->content;
		cmds = cmds->next;
		free_cmd(cur_cmd);
		free(current);
	}
}
