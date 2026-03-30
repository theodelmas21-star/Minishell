/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_states.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:19:15 by ssivilay          #+#    #+#             */
/*   Updated: 2026/03/30 02:39:30 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remove_dollar(t_lexer *lexer)
{
	int	len;

	len = ft_strlen(lexer->tmp);
	if (len > 0 && lexer->tmp[len - 1] == '$'
		&& (len < 2 || lexer->tmp[len - 2] != '$'))
		lexer->tmp[--len] = '\0';
	if (lexer->tmp[0])
		on_create_token(lexer, NO_QUOTE, 1);
	else
	{
		free(lexer->tmp);
		lexer->tmp = NULL;
	}
}

static void	handle_quotes_in_word(t_lexer *lexer, char c)
{
	if (c == '\'' || c == '\"')
	{
		if (lexer->tmp && lexer->tmp[0])
			remove_dollar(lexer);
		if (c == '\'')
			lexer->state = STATE_IN_SQUOTE;
		else
			lexer->state = STATE_IN_DQUOTE;
	}
}

void	handle_word(t_lexer *lexer, char c)
{
	if (is_space(c))
	{
		if (lexer->tmp)
			on_create_token(lexer, NO_QUOTE, 0);
		lexer->in_sequence = 0;
		lexer->prev_state = STATE_GENERAL;
		lexer->state = STATE_GENERAL;
	}
	else if (is_operator(c))
	{
		if (lexer->tmp)
			on_create_token(lexer, NO_QUOTE, 0);
		lexer->in_sequence = 0;
		lexer->prev_state = STATE_GENERAL;
		lexer->i--;
		lexer->state = STATE_GENERAL;
	}
	else if (c == '\'' || c == '\"')
		handle_quotes_in_word(lexer, c);
	else
		add_char_to_tmp(lexer, c);
}

void	handle_operator(t_lexer *lexer, char c)
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

void	handle_squotes(t_lexer *lexer, char c)
{
	if (c == '\'')
	{
		on_create_token(lexer, SQUOTE, 0);
		lexer->prev_state = STATE_IN_SQUOTE;
		lexer->state = STATE_IN_WORD;
		lexer->in_sequence = 1;
	}
	else
		add_char_to_tmp(lexer, c);
}

void	handle_dquotes(t_lexer *lexer, char c)
{
	if (c == '\"')
	{
		on_create_token(lexer, DQUOTE, 0);
		lexer->prev_state = STATE_IN_DQUOTE;
		lexer->state = STATE_IN_WORD;
		lexer->in_sequence = 1;
	}
	else
		add_char_to_tmp(lexer, c);
}
