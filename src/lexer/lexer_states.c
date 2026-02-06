/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:46:41 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/06 17:47:26 by ssivilay         ###   ########.fr       */
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
	if (is_space(c))
		return ;
	else if (c == '\'')
	{
		add_char_to_tmp(lexer, c);
		lexer->state = STATE_IN_SQUOTE;
	}
	else if (c == '\"')
	{
		if (lexer->state == STATE_GENERAL)
			add_char_to_tmp(lexer, c);
		lexer->state = STATE_IN_DQUOTE;
	}
	else if (is_operator(c))
		handle_operator(lexer, c);
	else
	{
		lexer->state = STATE_IN_WORD;
		add_char_to_tmp(lexer, c);
	}
}

static void	handle_squotes(t_lexer *lexer, char c)
{
	add_char_to_tmp(lexer, c);
	if (c == '\'' && lexer->tmp)
	{
		create_token(lexer);
		lexer->state = STATE_GENERAL;
	}
}

static void	handle_dquotes(t_lexer *lexer, char c)
{
	if (c == '\"' && is_space(lexer->input[lexer->i + 1]))
	{
		lexer->state = STATE_GENERAL;
	}
	if (c == '\"' && lexer->tmp)
	{
		lexer->state = STATE_GENERAL;
	}
	add_char_to_tmp(lexer, c);
}

static void	handle_word(t_lexer *lexer, char c)
{
	if (is_space(c) || is_operator(c))
	{
		create_token(lexer);
		lexer->state = STATE_GENERAL;
		lexer->i--;
	}
	else if (c == '\"')
		lexer->state = STATE_IN_DQUOTE;
	else
		add_char_to_tmp(lexer, c);
}

void	lexer_states(t_lexer *lexer, char c)
{
	if (lexer->state == STATE_GENERAL)
		handle_general(lexer, c);
	else if (lexer->state == STATE_IN_SQUOTE)
		handle_squotes(lexer, c);
	else if (lexer->state == STATE_IN_DQUOTE)
		handle_dquotes(lexer, c);
	else if (lexer->state == STATE_IN_WORD)
		handle_word(lexer, c);
}
