/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:08:01 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/25 21:51:35 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int check_pipe(t_token *tok, t_token *next)
{
	if (tok->type == PIPE)
	{
		if (!next)
			return (printf(">"), 0);
		if (next->type == PIPE)
			return (printf(">"), 0);
	}
}

static int is_redirection(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND 
		|| type == REDIR_HEREDOC)
		return (1);
	else
		return (0);
}

static int check_redir(t_token *tok, t_token *next)
{
	if (is_redirection(tok->type))
	{
		if (!next)
			return (printf("syntax error near unexpected token 'newline'"), 0);
		if (next->type != WORD)
			return (printf("syntax error near unexpected token '%s'", next->arg), 0);
	}
}

int check_args(t_list *tokens)
{
	t_token *tok;
	t_token *next;

	if (!tokens)
		return (0);
	tok = tokens->content;
	next = NULL;
	if (tok->type == PIPE)
		return (printf("syntax error near unexpected token '|'"), 0);
	while (tokens)
	{
		tok = tokens->content;

		if (tokens->next)
			next = tokens->next->content;
		else
			next = NULL;
		check_pipe(token, next);
		check_redir(token, next);
		tokens = tokens->next;
	}
	return (1);
}
