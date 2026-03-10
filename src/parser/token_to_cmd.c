/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:22:27 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/10 15:19:53 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = malloc(sizeof(char *));
	if (!cmd->cmd)
		return (free(cmd), NULL);
	cmd->is_expand = malloc(sizeof(int));
	if (!cmd->is_expand)
		return (free(cmd->cmd), free(cmd), NULL);
	cmd->cmd[0] = NULL;
	cmd->is_expand[0] = 0;
	cmd->redirs = NULL;
	cmd->is_builtin = 0;
	cmd->pipefd[0] = -1;
	cmd->pipefd[1] = -1;
	return (cmd);
}

static int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0 || ft_strncmp(cmd, "cd",
			ft_strlen(cmd)) == 0 || ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 || ft_strncmp(cmd,
			"unset", ft_strlen(cmd)) == 0 || ft_strncmp(cmd, "env",
			ft_strlen(cmd)) == 0 || ft_strncmp(cmd, "exit",
			ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}
static int	cmd_add_arg(t_cmd *cmd, t_token *tok)
{
	char	**new;
	int		*new_expand;
	int		i;

	i = 0;
	while (cmd->cmd[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (0);
	new_expand = malloc(sizeof(int) * (i + 1));
	if (!new_expand)
		return (free(new), 0);
	i = 0;
	while (cmd->cmd[i])
	{
		new[i] = cmd->cmd[i];
		new_expand[i] = cmd->is_expand[i];
		i++;
	}
	new[i] = ft_strdup(tok->arg);
	new_expand[i] = is_expandable(tok->arg) && tok->quote_type != SQUOTE;
	new[i + 1] = NULL;
	free(cmd->cmd);
	free(cmd->is_expand);
	cmd->cmd = new;
	cmd->is_expand = new_expand;
	cmd->is_builtin = is_builtin(cmd->cmd[0]);
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
		cmd_add_arg(*cmd, tok);
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
			return (free_cmd(cmd), free_cmds(cmd_list), NULL);
		tokens = tokens->next;
	}
	ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
	return (cmd_list);
}

/* int	get_quote_type(t_token *token)
{
	t_list	*current;
	t_token	*subtoken;
	t_list	*cmd_list;
	t_cmd	*cmd;
	t_token	*tok;
	t_list	*cmd_list;
	t_cmd	*cmd;
	t_token	*tok;

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
