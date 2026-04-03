/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:22:27 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 13:57:22 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*token_to_cmd(t_list *tokens)
{
	t_list	*cmd_list;
	t_cmd	*cmd;
	t_token	*tok;

	cmd_list = NULL;
	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	while (tokens)
	{
		tok = tokens->content;
		if (!create_cmd_list(tok, &cmd, tokens, &cmd_list))
			return (free_cmd(cmd), free_cmds(cmd_list), NULL);
		if (is_redirection(tok->type))
			tokens = tokens->next->next;
		else
			tokens = tokens->next;
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	return (cmd_list);
}
