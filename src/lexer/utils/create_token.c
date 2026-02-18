/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:29:48 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/18 17:33:38 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	create_subtoken(t_lexer *lexer, t_quote quote_type)
{
	t_token	*subtoken;
	t_list	*node;
	t_list	*last_token;
	t_token	*last_tok_content;

	if (!lexer->tmp)
	{
		if (quote_type != NO_QUOTE)
			lexer->tmp = ft_strdup("");
		else
			return ;
	}
	else if (!lexer->tmp[0] && quote_type == NO_QUOTE)
	{
		free(lexer->tmp);
		lexer->tmp = NULL;
		return ;
	}
	subtoken = malloc(sizeof(t_token));
	if (!subtoken)
		return ;
	subtoken->subtokens = NULL;
	subtoken->arg = lexer->tmp;
	subtoken->type = WORD;
	subtoken->quote_type = quote_type;
	node = ft_lstnew(subtoken);
	last_token = ft_lstlast(lexer->tokens);
	if (!last_token)
	{
		ft_lstadd_back(&lexer->tokens, node);
		lexer->in_sequence = 0;
	}
	else
	{
		last_tok_content = (t_token *)last_token->content;
		ft_lstadd_back(&last_tok_content->subtokens, node);
	}
	lexer->tmp = NULL;
}

void	create_token(t_lexer *lexer, t_quote quote_type)
{
	t_token *token;
	t_list *node;

	if (!lexer->tmp)
	{
		if (quote_type != NO_QUOTE)
			lexer->tmp = ft_strdup("");
		else
			return ;
	}
	else if (!lexer->tmp[0] && quote_type == NO_QUOTE)
	{
		free(lexer->tmp);
		lexer->tmp = NULL;
		return ;
	}
	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	token->subtokens = NULL;
	token->arg = lexer->tmp;
	token->type = get_token_type(token->arg);
	token->quote_type = quote_type;
	node = ft_lstnew(token);
	ft_lstadd_back(&lexer->tokens, node);
	lexer->tmp = NULL;
	lexer->in_sequence = 0;
}