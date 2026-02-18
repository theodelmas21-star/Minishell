/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:55:36 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/17 21:42:41 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*lexer(char *input)
{
	t_lexer	lexer;

	lexer.input = input;
	lexer.i = 0;
	lexer.state = STATE_GENERAL;
	lexer.prev_state = STATE_GENERAL;
	lexer.tmp = NULL;
	lexer.tokens = NULL;
	lexer.in_sequence = 0;
	
	if (!input)
		return (NULL);
	
	while (input[lexer.i])
	{
		lexer_states(&lexer, input[lexer.i]);
		lexer.i++;
	}
	if (lexer.state == STATE_IN_SQUOTE || lexer.state == STATE_IN_DQUOTE)
	{
		ft_putendl_fd("minishell: unclosed quote", 2);
		free(lexer.tmp);
		//ft_lstclear(&lexer.tokens, free_token_content);
		return (NULL);
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
