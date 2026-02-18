/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:46:41 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/17 21:42:27 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int	should_create_subtoken(t_lexer *lexer)
{
	if (!lexer->tokens)
		return (0);
	
	if (lexer->state == STATE_IN_WORD 
		&& (lexer->prev_state == STATE_IN_SQUOTE 
			|| lexer->prev_state == STATE_IN_DQUOTE
			|| lexer->prev_state == STATE_IN_WORD))
	{
		return (1);
	}
	
	return (0);
}
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
	{
		lexer->prev_state = STATE_GENERAL;
		return ;
	}
	else if (c == '\'')
	{
		lexer->state = STATE_IN_SQUOTE;
	}
	else if (c == '\"')
	{
		lexer->state = STATE_IN_DQUOTE;
	}
	else if (is_operator(c))
	{
		handle_operator(lexer, c);
		lexer->prev_state = STATE_GENERAL;
	}
	else
	{
		add_char_to_tmp(lexer, c);
		lexer->state = STATE_IN_WORD;
	}
}

static void	handle_squotes(t_lexer *lexer, char c)
{
	if (c == '\'')
	{
		if (lexer->in_sequence)
			create_subtoken(lexer, SQUOTE);
		else
			create_token(lexer, SQUOTE);
		
		lexer->prev_state = STATE_IN_SQUOTE;
		lexer->state = STATE_IN_WORD;
		lexer->in_sequence = 1;
	}
	else
		add_char_to_tmp(lexer, c);
}

static void	handle_dquotes(t_lexer *lexer, char c)
{
	if (c == '\"')
	{
		if (lexer->in_sequence)
			create_subtoken(lexer, DQUOTE);
		else
			create_token(lexer, DQUOTE);
		
		lexer->prev_state = STATE_IN_DQUOTE;
		lexer->state = STATE_IN_WORD;
		lexer->in_sequence = 1;
	}
	else
		add_char_to_tmp(lexer, c);
}

static void	handle_word(t_lexer *lexer, char c)
{
	if (is_space(c))
	{
		if (lexer->tmp)
		{
			if (lexer->in_sequence)
				create_subtoken(lexer, NO_QUOTE);
			else
				create_token(lexer, NO_QUOTE);
		}
		lexer->in_sequence = 0;
		lexer->prev_state = STATE_GENERAL;
		lexer->state = STATE_GENERAL;
	}
	else if (is_operator(c))
	{
		if (lexer->tmp)
		{
			if (lexer->in_sequence)
				create_subtoken(lexer, NO_QUOTE);
			else
				create_token(lexer, NO_QUOTE);
		}
		lexer->in_sequence = 0;
		lexer->prev_state = STATE_GENERAL;
		lexer->i--;
		lexer->state = STATE_GENERAL;
	}
	else if (c == '\'')
	{
		if (lexer->tmp && lexer->tmp[0])
		{
			if (lexer->in_sequence)
				create_subtoken(lexer, NO_QUOTE);
			else
			{
				create_token(lexer, NO_QUOTE);
				lexer->in_sequence = 1;
			}
		}
		lexer->state = STATE_IN_SQUOTE;
	}
	else if (c == '\"')
	{
		if (lexer->tmp && lexer->tmp[0])
		{
			if (lexer->in_sequence)
				create_subtoken(lexer, NO_QUOTE);
			else
			{
				create_token(lexer, NO_QUOTE);
				lexer->in_sequence = 1;
			}
		}
		lexer->state = STATE_IN_DQUOTE;
	}
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
