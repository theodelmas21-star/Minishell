/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:17:01 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/30 02:57:28 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	apply_redirections(t_cmd *cmds, t_env *s_env, t_exec exc)
{
	t_list	*current;
	t_redir	*redir_R;
	int		saved_stdin;

	if (!cmds || !cmds->redirs)
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	current = cmds->redirs;
	while (current)
	{
		redir_R = (t_redir *)current->content;
		if (redir_R->type == REDIR_HEREDOC)
			dup2(saved_stdin, STDIN_FILENO);
		if (apply_all_redirs(*redir_R, s_env, exc) != 0)
			return (close(saved_stdin), 1);
		current = current->next;
	}
	close(saved_stdin);
	return (0);
}
