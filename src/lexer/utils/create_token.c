/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:29:48 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/23 14:12:28 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	check_empty_quotes(t_lexer *lexer, t_quote quote_type)
{
	if (!lexer->tmp)
	{
		if (quote_type != NO_QUOTE)
		{
			lexer->tmp = ft_strdup("");
			if (!lexer->tmp)
				return ;
		}
		else
			return ;
	}
	else if (!lexer->tmp[0] && quote_type == NO_QUOTE)
	{
		free(lexer->tmp);
		lexer->tmp = NULL;
		return ;
	}
}

static void	add_subtoken(t_list *last_token, t_lexer *lexer, t_list *node)
{
	t_token	*last_tok_content;

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
}

void	create_subtoken(t_lexer *lexer, t_quote quote_type)
{
	t_token	*subtoken;
	t_list	*node;
	t_list	*last_token;

	check_empty_quotes(lexer, quote_type);
	subtoken = malloc(sizeof(t_token));
	if (!subtoken)
	{
		free(lexer->tmp);
		lexer->tmp = NULL;
		return ;
	}
	subtoken->subtokens = NULL;
	subtoken->arg = NULL;
	if (lexer->tmp)
		subtoken->arg = lexer->tmp;
	subtoken->type = WORD;
	subtoken->quote_type = quote_type;
	node = ft_lstnew(subtoken);
	if (!node)
		return (del_token(subtoken));
	last_token = ft_lstlast(lexer->tokens);
	add_subtoken(last_token, lexer, node);
	lexer->tmp = NULL;
}

void	create_token(t_lexer *lexer, t_quote quote_type)
{
	t_token	*token;
	t_list	*node;

	check_empty_quotes(lexer, quote_type);
	token = malloc(sizeof(t_token));
	if (!token)
	{
		free(lexer->tmp);
		lexer->tmp = NULL;
		return ;
	}
	token->subtokens = NULL;
	token->arg = NULL;
	if (lexer->tmp)
		token->arg = lexer->tmp;
	token->type = get_token_type(token->arg);
	token->quote_type = quote_type;
	node = ft_lstnew(token);
	if (!node)
		return (del_token(token));
	ft_lstadd_back(&lexer->tokens, node);
	lexer->tmp = NULL;
	lexer->in_sequence = 0;
}

void	on_create_token(t_lexer *lexer, t_quote quote_type, int in_sequence)
{
	if (lexer->in_sequence)
		create_subtoken(lexer, quote_type);
	else
	{
		create_token(lexer, quote_type);
		if (in_sequence)
			lexer->in_sequence = 1;
	}
}
