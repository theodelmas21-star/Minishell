/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:22:27 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/15 16:50:44 by tdelmas2         ###   ########.fr       */
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
		cmd->cmd[i++] = s_token->arg;
		tokens = tokens->next;
	}
	cmd->cmd[i] = NULL;
	cmd->redirs = NULL;
	cmd->is_builtin = 0;
	cmd->pipefd[0] = 0;
	cmd->pipefd[1] = 0;
	return (cmd);
}

t_list *create_list_cmd(t_list *list_cmd, t_list *tokens)
{
	t_list *cur_cmd;
	t_cmd *cmd;
	
	cmd = create_cmd(tokens);
	if (!cmd)
		return (NULL);	
	cur_cmd = ft_lstnew(cmd);
	if (!cur_cmd)
		return (free_tab(cmd->cmd), free(cmd), NULL);
	cur_cmd->next = NULL;
	ft_lstadd_back(&list_cmd, cur_cmd);
	return (list_cmd);
}

t_list	*token_to_cmd(t_list *tokens)
{
	t_list *list_cmd;
	
	if (!tokens)
		return (NULL);
	list_cmd = NULL;
	while (tokens)
	{
		list_cmd = create_list_cmd(list_cmd, tokens);
		if (list_cmd == NULL)
			return (NULL);
		while (tokens)
		{
			if (((t_token *)tokens->content)->type != WORD)
				break;
			tokens = tokens->next;
		}
		if (tokens && ((t_token *)tokens->content)->type == PIPE)
			tokens = tokens->next;
	}
	return (list_cmd);
} 
