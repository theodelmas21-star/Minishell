/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:46:41 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/05 11:54:59 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_operator(t_lexer *lexer, char c)
{
	if (lexer->tmp)
		create_token(lexer);
	add_char_to_tmp(lexer, c);
	if ((c == '<' || c == '>') && lexer->input[lexer->i + 1] == c)
	{
		lexer->i++;
		add_char_to_tmp(lexer, c);
	}
	create_token(lexer);
	lexer->state = STATE_GENERAL;
}

static void	handle_general(t_lexer *lexer, char c)
{
	if (c == ' ')
		return ;
	else if (c == '\'')
	{
		if (!lexer->tmp)
			add_char_to_tmp(lexer, c);
		lexer->state = STATE_IN_SQUOTE;
	}
	else if (c == '\"')
	{
		if (!lexer->tmp)
			add_char_to_tmp(lexer, c);
		lexer->state = STATE_IN_DQUOTE;
	}
	else if (c == '|' || c == '<' || c == '>')
		handle_operator(lexer, c);
	else
	{
		lexer->state = STATE_IN_WORD;
		add_char_to_tmp(lexer, c);
	}
}

static void	handle_quotes(t_lexer *lexer, char c)
{
	if ((c == '\'' || c == '\"') && lexer->tmp)
	{
		add_char_to_tmp(lexer, c);
		create_token(lexer);
		lexer->state = STATE_GENERAL;
	}
	else
		add_char_to_tmp(lexer, c);
}

static void	handle_word(t_lexer *lexer, char c)
{
	if (c == ' ' || c == '\'' || c == '"' || c == '|' || c == '<' || c == '>')
	{
		create_token(lexer);
		lexer->state = STATE_GENERAL;
	}
	else
		add_char_to_tmp(lexer, c);
}

void	lexer_states(t_lexer *lexer, char c)
{
	if (lexer->state == STATE_GENERAL)
		handle_general(lexer, c);
	else if (lexer->state == STATE_IN_SQUOTE || lexer->state == STATE_IN_DQUOTE)
		handle_quotes(lexer, c);
	else if (lexer->state == STATE_IN_WORD)
		handle_word(lexer, c);
}
