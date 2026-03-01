/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:17:01 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/01 15:33:22 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	apply_redirections(t_cmd *cmds, t_env *s_env, t_exec exc)
{
	t_list	*current;
	t_redir	*redir_R;

	if (!cmds || !cmds->redirs)
		return (0);
	current = cmds->redirs;
	while (current)
	{
		redir_R = (t_redir *)current->content;
        if (apply_all_redirs(*redir_R, s_env, exc) != 0)
            return (1);
		current = current->next;
	}
	return (0);
}
