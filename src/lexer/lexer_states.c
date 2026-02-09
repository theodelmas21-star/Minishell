/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:46:41 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/09 16:23:57 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_operator(t_lexer *lexer, char c)
{
	if (lexer->tmp)
		create_token(lexer, NO_QUOTE);
	add_char_to_tmp(lexer, c);
	if ((c == '<' || c == '>') && lexer->input[lexer->i + 1] == c)
	{
		lexer->i++;
		add_char_to_tmp(lexer, c);
	}
	create_token(lexer, NO_QUOTE);
	lexer->state = STATE_GENERAL;
}

static void	handle_general(t_lexer *lexer, char c)
{
	if (is_space(c))
		return ;
	else if (c == '\'')
	{
		if (lexer->input[lexer->i + 1] == '\'')
		{
			add_char_to_tmp(lexer, c);
			lexer->i++;
			add_char_to_tmp(lexer, c);
			create_token(lexer, SQUOTE);
			lexer->state = STATE_GENERAL;
		}
		else
			lexer->state = STATE_IN_SQUOTE;
	}
	else if (c == '\"')
	{
		if (lexer->input[lexer->i + 1] == '\"')
		{
			add_char_to_tmp(lexer, c);
			lexer->i++;
			add_char_to_tmp(lexer, c);
			create_token(lexer, DQUOTE);
			lexer->state = STATE_GENERAL;
		}
		else
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
	if ((c == '\'' && (lexer->input[lexer->i + 1] == ' '
			|| lexer->input[lexer->i + 1] == '\0')) || lexer->input[lexer->i
			+ 1] == '\0')
	{
		if (c != '\'')
			add_char_to_tmp(lexer, c);
		create_token(lexer, SQUOTE);
		lexer->state = STATE_GENERAL;
	}
	else if ((c == '\'' && (lexer->input[lexer->i + 1] != ' '
			|| lexer->input[lexer->i + 1] != '\0')))
		return ;
	else
		add_char_to_tmp(lexer, c);
}

static void	handle_dquotes(t_lexer *lexer, char c)
{
	if ((c == '\"' && (lexer->input[lexer->i + 1] == ' '
				|| lexer->input[lexer->i + 1] == '\0')) || lexer->input[lexer->i
		+ 1] == '\0')
	{
		if (c != '\"')
			add_char_to_tmp(lexer, c);
		create_token(lexer, DQUOTE);
		lexer->state = STATE_GENERAL;
	}
	else if ((c == '\"' && (lexer->input[lexer->i + 1] != ' '
				|| lexer->input[lexer->i + 1] != '\0')))
		return ;
	else
		add_char_to_tmp(lexer, c);
}

static void	handle_word(t_lexer *lexer, char c)
{
	if (is_space(c) || is_operator(c))
	{
		if (is_operator(c))
			handle_operator(lexer, c);
		else
			create_token(lexer, NO_QUOTE);
		lexer->state = STATE_GENERAL;
	}
	else if (c == '\'')
		lexer->state = STATE_IN_SQUOTE;
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
