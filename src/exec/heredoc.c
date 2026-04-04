/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 22:10:23 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/04 16:51:33 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_heredoc_fds(t_list *cmds)
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
			if (redir->type == REDIR_HEREDOC && redir->fd != -1)
			{
				close(redir->fd);
				redir->fd = -1;
			}
			cur_redir = cur_redir->next;
		}
		cur_cmd = cur_cmd->next;
	}
}

void	close_heredoc_fds(t_list *head, t_list *current_cmd)
{
	t_list	*cur_cmd;
	t_list	*cur_redir;
	t_cmd	*cmd;
	t_redir	*redir;

	cur_cmd = head;
	while (cur_cmd)
	{
		if (cur_cmd != current_cmd)
		{
			cmd = (t_cmd *)cur_cmd->content;
			cur_redir = cmd->redirs;
			while (cur_redir)
			{
				redir = (t_redir *)cur_redir->content;
				if (redir->type == REDIR_HEREDOC && redir->fd != -1)
				{
					close(redir->fd);
					redir->fd = -1;
				}
				cur_redir = cur_redir->next;
			}
		}
		cur_cmd = cur_cmd->next;
	}
}

void	signal_hd(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g_signal = 130;
	close(0);
}

int	handle_heredocs(t_list *cmds, t_env *s_env, t_exec *exc)
{
	t_hd_helper	h;

	h.cur_cmd = cmds;
	signal(SIGINT, signal_hd);
	while (h.cur_cmd)
	{
		h.cmd = (t_cmd *)h.cur_cmd->content;
		h.cur_redir = h.cmd->redirs;
		while (h.cur_redir)
		{
			h.redir = (t_redir *)h.cur_redir->content;
			if (h.redir->type == REDIR_HEREDOC)
			{
				if (hd_manage(h.redir, s_env, *exc) != 0)
				{
					close_all_heredoc_fds(cmds);
					return (init_signal(), 1);	
				}
				h.redir->fd = open("/tmp/minishell_hd", O_RDONLY);
			}
			h.cur_redir = h.cur_redir->next;
		}
		h.cur_cmd = h.cur_cmd->next;
	}
	init_signal();
	return (0);
}
