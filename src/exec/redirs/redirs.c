/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:17:01 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 22:19:20 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	apply_redirections(t_cmd *cmds, t_env *s_env, t_exec exc)
{
	t_list	*current;
	t_redir	*redir_r;

	if (!cmds || !cmds->redirs)
		return (0);
	current = cmds->redirs;
	while (current)
	{
		redir_r = (t_redir *)current->content;
		if (redir_r->target && ft_strchr(redir_r->target, '$'))
		{
			redir_r->target = expand_hd(redir_r->target, s_env, &exc, 0);
			if (!redir_r->target && exc.error == 1)
				return (close(1));
		}
		if (apply_all_redirs(*redir_r, s_env, exc) != 0)
			return (1);
		current = current->next;
	}
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
