/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:48:55 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/16 19:00:08 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	add_char_to_tmp(t_lexer *lexer, char c)
{
	char	*new_tmp;
	int		len;

	if (!lexer->tmp)
		len = 0;
	else
		len = ft_strlen(lexer->tmp);
	new_tmp = malloc(len + 2);
	if (!new_tmp)
		return ;
	if (lexer->tmp)
	{
		ft_strlcpy(new_tmp, lexer->tmp, len + 1);
		free(lexer->tmp);
	}
	new_tmp[len] = c;
	new_tmp[len + 1] = '\0';
	lexer->tmp = new_tmp;
}

t_token_type	get_token_type(char *arg)
{
	if (ft_strncmp(arg, "|", 1) == 0 && ft_strlen(arg) == 1)
		return (PIPE);
	else if (ft_strncmp(arg, "<<", 2) == 0 && ft_strlen(arg) == 2)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(arg, ">>", 2) == 0 && ft_strlen(arg) == 2)
		return (REDIR_APPEND);
	else if (ft_strncmp(arg, "<", 1) == 0 && ft_strlen(arg) == 1)
		return (REDIR_IN);
	else if (ft_strncmp(arg, ">", 1) == 0 && ft_strlen(arg) == 1)
		return (REDIR_IN);
	else
		return (WORD);
}

void	create_subtoken(t_lexer *lexer, t_quote quote_type)
{
	t_token	*subtoken;
	t_list	*node;
	t_list	*last_token;
	t_token	*last_tok_content;

	if (!lexer->tmp || !lexer->tmp[0])
		return ;
	subtoken = malloc(sizeof(t_token));
	if (!subtoken)
		return ;
	subtoken->subtokens = NULL;
	subtoken->arg = ft_strdup(lexer->tmp);
	subtoken->type = get_token_type(subtoken->arg);
	subtoken->quote_type = quote_type;
	node = ft_lstnew(subtoken);
	last_token = ft_lstlast(lexer->tokens);
	if (!last_token)
	{
		free(subtoken->arg);
		free(subtoken);
		return ;
	}
	last_tok_content = (t_token *)last_token->content;
	ft_lstadd_back(&last_tok_content->subtokens, node);
	lexer->tmp = NULL;
}

void	create_token(t_lexer *lexer, t_quote quote_type)
{
	t_token	*token;
	t_list	*node;

	if (!lexer->tmp || !lexer->tmp[0])
		return ;
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
}
