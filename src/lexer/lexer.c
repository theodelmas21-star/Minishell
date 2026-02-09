/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:55:36 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/09 13:54:31 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*lexer(char *input)
{
	t_lexer	lexer;

	lexer.input = input;
	lexer.i = 0;
	lexer.state = STATE_GENERAL;
	lexer.tmp = NULL;
	lexer.tokens = NULL;
	if (!input)
		return (NULL);
	while (input[lexer.i])
	{
		lexer_states(&lexer, input[lexer.i]);
		printf("[%d]%c = %d\n", lexer.i, input[lexer.i], lexer.state);
		lexer.i++;
	};
	if (lexer.state == STATE_IN_SQUOTE || lexer.state == STATE_IN_DQUOTE)
		return (NULL);
	if (lexer.tmp)
		create_token(&lexer, NO_QUOTE);
	free(lexer.tmp);
	return (lexer.tokens);
}
