/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:22:27 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/26 15:27:04 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->cmd = malloc(sizeof(char *));
	if (!cmd->cmd)
		return (free(cmd), NULL);
	cmd->cmd[0] = NULL;
	cmd->pipefd[0] = -1;
	cmd->pipefd[1] = -1;
	return (cmd);
}

static int	cmd_add_arg(t_cmd *cmd, char *arg)
{
	char	**new;
	int		i;

	i = 0;
	while (cmd->cmd[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (0);
	i = 0;
	while (cmd->cmd[i])
	{
		new[i] = cmd->cmd[i];
		i++;
	}
	new[i++] = arg;
	new[i] = NULL;
	free(cmd->cmd);
	cmd->cmd = new;
	return (1);
}

static int	add_redirection(t_cmd *cmd, t_token *redir, t_token *target)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->type = redir->type;
	new->target = target->arg;
	new->limiter = NULL;
	new->fd = -1;
	ft_lstadd_back(&cmd->redirs, ft_lstnew(new));
	return (1);
}

static int	create_cmd_list(t_token *tok, t_cmd **cmd, t_list *tokens,
		t_list **cmd_list)
{
	t_token	*target;

	if (tok->type == WORD)
	{
		cmd_add_arg(*cmd, tok->arg);
		return (1);
	}
	else if (is_redirection(tok->type))
	{
		if (!tokens->next)
			return (0);
		target = tokens->next->content;
		add_redirection(*cmd, tok, target);
		tokens = tokens->next;
		return (1);
	}
	else if (tok->type == PIPE)
	{
		ft_lstadd_back(cmd_list, ft_lstnew(*cmd));
		*cmd = init_cmd();
		if (!*cmd)
			return (0);
		return (1);
	}
	return (1);
}

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
			return (NULL);
		tokens = tokens->next;
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	return (cmd_list);
}
