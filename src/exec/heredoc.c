/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 22:10:23 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 22:11:13 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_heredocs(t_list *cmds, t_env *s_env, t_exec *exc)
{
	t_list	*cur_cmd;
	t_list	*cur_redir;
	t_cmd	*cmd;
	t_redir	*redir;

	cur_cmd = cmds;
	while (cur_cmd)
	{
		cmd = (t_cmd *)cur_cmd->content;
		cur_redir = cmd->redirs;
		while (cur_redir)
		{
			redir = (t_redir *)cur_redir->content;
			if (redir->type == REDIR_HEREDOC)
			{
				if (hd_manage(redir, s_env, *exc) != 0)
					return (1);
				redir->fd = open("tmp", O_RDONLY);
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
	return (0);
}
