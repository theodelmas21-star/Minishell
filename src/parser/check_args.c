/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:08:01 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/26 14:32:59 by ssivilay         ###   ########.fr       */
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
	return (1);
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
	return (1);
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
		check_pipe(tok, next);
		check_redir(tok, next);
		tokens = tokens->next;
	}
	return (1);
}
