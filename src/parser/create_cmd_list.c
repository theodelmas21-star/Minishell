/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:57:10 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/03 15:19:45 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	build_hd_delim(t_redir *new, t_token *target)
{
	t_list	*sub;
	t_token	*stok;

	new->delimiter = ft_strdup(target->arg);
	if (!new->delimiter)
		return (0);
	new->exp_hd = target->quote_type == NO_QUOTE;
	sub = target->subtokens;
	while (sub)
	{
		stok = (t_token *)sub->content;
		if (stok->quote_type != NO_QUOTE)
			new->exp_hd = 0;
		new->delimiter = ft_strjoin_free(new->delimiter, stok->arg,
				new->delimiter);
		if (!new->delimiter)
			return (0);
		sub = sub->next;
	}
	return (1);
}

int	add_redirection(t_cmd *cmd, t_token *redir, t_token *target)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->type = redir->type;
	new->target = NULL;
	new->delimiter = NULL;
	new->fd = -1;
	if (redir->type == REDIR_HEREDOC)
	{
		if (!build_hd_delim(new, target))
			return (free(new), 0);
	}
	else
	{
		new->target = ft_strdup(target->arg);
		if (!new->target)
			return (free(new), 0);
		new->exp_hd = target->quote_type == NO_QUOTE;
	}
	ft_lstadd_back(&cmd->redirs, ft_lstnew(new));
	return (1);
}

void	add_subtokens(t_cmd *cmd, t_token *tok, int *is_new)
{
	t_list	*sub_tok;
	t_token	*sub_tok_content;

	sub_tok = tok->subtokens;
	while (sub_tok)
	{
		sub_tok_content = (t_token *)sub_tok->content;
		cmd_add_arg(cmd, sub_tok_content->arg, sub_tok_content->quote_type,
			*is_new);
		if (ft_strlen(tok->arg) < 1 && *is_new)
			*is_new = 0;
		sub_tok = sub_tok->next;
	}
}

int	handle_word_tok(t_cmd *cmd, t_token *tok)
{
	int		is_new;
	char	*arg;
	t_quote	qt;
	t_list	*last;

	is_new = 1;
	arg = tok->arg;
	qt = tok->quote_type;
	if (ft_strlen(arg) > 0)
	{
		cmd_add_arg(cmd, arg, qt, 1);
		is_new = 0;
	}
	add_subtokens(cmd, tok, &is_new);
	last = ft_lstlast(tok->subtokens);
	if (last)
	{
		arg = ((t_token *)last->content)->arg;
		qt = ((t_token *)last->content)->quote_type;
	}
	if (ft_strlen(arg) < 1)
		cmd_add_arg(cmd, arg, qt, is_new);
	return (1);
}

int	create_cmd_list(t_token *tok, t_cmd **cmd, t_list *tokens,
		t_list **cmd_list)
{
	if (tok->type == WORD)
		return (handle_word_tok(*cmd, tok));
	else if (is_redirection(tok->type))
	{
		if (!tokens->next)
			return (0);
		return (add_redirection(*cmd, tok, tokens->next->content));
	}
	else if (tok->type == PIPE)
	{
		ft_lstadd_back(cmd_list, ft_lstnew(*cmd));
		*cmd = init_cmd();
		if (!*cmd)
			return (0);
	}
	return (1);
}
