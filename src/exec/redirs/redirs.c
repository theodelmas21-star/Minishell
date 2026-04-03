/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:17:01 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 14:45:17 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	apply_redirections(t_cmd *cmds, t_env *s_env, t_exec exc)
{
	t_list	*current;
	t_redir	*redir_r;
	int		saved_stdin;

	if (!cmds || !cmds->redirs)
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	current = cmds->redirs;
	while (current)
	{
		redir_r = (t_redir *)current->content;
		if (redir_r->type == REDIR_HEREDOC)
			dup2(saved_stdin, STDIN_FILENO);
		if (redir_r->target && ft_strchr(redir_r->target, '$'))
		{
			redir_r->target = expand_hd(redir_r->target, s_env, &exc, 0);
			if (!redir_r->target && exc.error == 1)
				return (close(saved_stdin), 1);
		}
		if (apply_all_redirs(*redir_r, s_env, exc) != 0)
			return (close(saved_stdin), 1);
		current = current->next;
	}
	close(saved_stdin);
	return (0);
}

int	stop_hd(char *tmp, t_redir *redir_R)
{
	int	len;

	len = ft_strlen(redir_R->delimiter);
	if (ft_strncmp(tmp, redir_R->delimiter, len) != 0)
		return (0);
	if (tmp[len] == '\n' || tmp[len] == '\0')
		return (1);
	return (0);
}
