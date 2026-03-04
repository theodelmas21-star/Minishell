/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:22:27 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/04 08:34:31 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	size_cmd_parser(t_list *tokens)
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

/* int	get_quote_type(t_token *token)
{
	t_list	*current;
	t_token	*subtoken;

	if (!token)
		return (1);
	if (token->quote_type == DQUOTE)
		return (2);
	current = token->subtokens;
	while (current)
	{
		subtoken = (t_token *)current->content;
		if (subtoken && subtoken->quote_type == DQUOTE)
			return (2);
		current = current->next;
	}
	return (1);
}*/

t_cmd	*create_cmd(t_list *tokens)
{
	t_cmd	*cmd;
	t_token *s_token;
	int		size;
	int		i;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	size = size_cmd_parser(tokens);
	cmd->cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd->cmd)
		return (free(cmd), NULL);
	/* allocate expansion flags once, initialize all to 0 */
	cmd->is_expand = malloc(sizeof(int) * size);
	if (!cmd->is_expand)
		return (free_tab(cmd->cmd), free(cmd), NULL);
	ft_memset(cmd->is_expand, 0, sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		s_token = (t_token *)tokens->content;
		//cmd->is_expand[i] = get_quote_type(s_token);
		cmd->is_expand[i] = 2;
		cmd->is_builtin = 1 ;
		cmd->cmd[i++] = s_token->arg;
		tokens = tokens->next;
	}
	cmd->cmd[i] = NULL;
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
