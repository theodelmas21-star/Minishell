/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:22:27 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/10 13:53:54 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_cmd(t_list *tokens)
{
	t_token *s_token;
	int		size;
	
	size = 0;
	if (!tokens)
		return (0);
	while (tokens)
	{
		s_token = (t_token *)tokens->content;
		if (s_token->type != WORD)
			break;
		tokens = tokens->next;
		size++;
	}
	return (size);
}

t_cmd	*create_cmd(t_list *tokens)
{
	t_cmd	*cmd;
	t_token *s_token;
	int		size;
	int		i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	size = size_cmd(tokens);
	cmd->cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd->cmd)
		return (free(cmd), NULL);
	i = 0;
	while (i < size)
	{
		s_token = (t_token *)tokens->content;
		if (s_token->type != WORD)
			break;
		cmd->cmd[i++] = s_token->arg;
		tokens = tokens->next;
	}
	cmd->cmd[i] = NULL;
	return (cmd);
}

t_cmd	*token_to_cmd(t_list *tokens)
{
	t_cmd *cmd;
	
	if (!tokens)
		return (NULL);
	cmd = create_cmd(tokens);
	return (cmd);
} 
