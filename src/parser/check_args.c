/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:08:01 by ssivilay          #+#    #+#             */
/*   Updated: 2026/03/19 14:17:11 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_pipe(t_token *tok, t_token *next)
{
	if (tok->type == PIPE)
	{
		if (!next)
			return (printf(">"), 1);
		if (next->type == PIPE)
			return (printf("minishell: syntax error near unexpected token '%s'\n",
					next->arg), 1);
	}
	return (0);
}
static int	check_redir(t_token *tok, t_token *next)
{
	if (is_redirection(tok->type))
	{
		if (!next)
			return (printf("minishell: syntax error near unexpected token 'newline'\n"),
				1);
		if (next->type != WORD)
			return (printf("minishell: syntax error near unexpected token '%s'\n",
					next->arg), 1);
	}
	return (0);
}

static int	check_char(t_token *tok)
{
	if (ft_strlen(tok->arg) > 0)
		if (ft_strncmp(tok->arg, ":", ft_strlen(tok->arg)) == 0
			|| ft_strncmp(tok->arg, "!", ft_strlen(tok->arg)) == 0)
			return (1);
	return (0);
}

int	check_args(t_list *tokens)
{
	t_token	*tok;
	t_token	*next;

	if (!tokens)
		return (0);
	tok = tokens->content;
	next = NULL;
	if (tok->type == PIPE)
		return (printf("minishell: syntax error near unexpected token '|'\n"),
			0);
	while (tokens)
	{
		tok = tokens->content;
		if (tokens->next)
			next = tokens->next->content;
		else
			next = NULL;
		if (check_char(tok) || check_pipe(tok, next) || check_redir(tok, next))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}
