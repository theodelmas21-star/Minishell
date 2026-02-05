/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:48:55 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/05 16:30:32 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	create_token(t_lexer *lexer)
{
	t_token	*token;
	t_list	*node;

	if (!lexer->tmp || !lexer->tmp[0])
		return ;
	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	token->arg = lexer->tmp;
	token->type = get_token_type(token->arg);
	node = ft_lstnew(token);
	ft_lstadd_back(&lexer->tokens, node);
	lexer->tmp = NULL;
}
