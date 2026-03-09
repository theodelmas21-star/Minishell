/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:55:36 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/24 14:55:09 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_lexer(t_lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->i = 0;
	lexer->state = STATE_GENERAL;
	lexer->prev_state = STATE_GENERAL;
	lexer->in_sequence = 0;
	lexer->tmp = NULL;
	lexer->tokens = NULL;
}

t_list	*lexer(char *input)
{
	t_lexer	lexer;

	init_lexer(&lexer, input);
	if (!input)
		return (NULL);
	while (input[lexer.i])
	{
		lexer_states(&lexer, input[lexer.i]);
		lexer.i++;
	}
	if (lexer.state == STATE_IN_SQUOTE || lexer.state == STATE_IN_DQUOTE)
	{
		ft_lstclear(&lexer.tokens, del_token);
		return (ft_putendl_fd(">", 2), free(lexer.tmp), NULL);
	}
	if (lexer.tmp)
	{
		if (lexer.in_sequence)
			create_subtoken(&lexer, NO_QUOTE);
		else
			create_token(&lexer, NO_QUOTE);
	}
	free(lexer.tmp);
	return (lexer.tokens);
}
