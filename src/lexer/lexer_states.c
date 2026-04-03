/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:46:41 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/03 15:20:01 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_general(t_lexer *lexer, char c)
{
	if (is_space(c))
	{
		lexer->prev_state = STATE_GENERAL;
		return ;
	}
	else if (c == '\'')
		lexer->state = STATE_IN_SQUOTE;
	else if (c == '\"')
		lexer->state = STATE_IN_DQUOTE;
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
