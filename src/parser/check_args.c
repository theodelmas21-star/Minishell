/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:08:01 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/03 13:54:17 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_tokens(t_list *tokens, t_token *tok)
{
	t_token	*next;
	int		ret;
	int		is_cmd;

	is_cmd = 1;
	while (tokens)
	{
		tok = tokens->content;
		if (tokens->next)
			next = tokens->next->content;
		else
			next = NULL;
		ret = check_token(tok, next, is_cmd);
		if (ret != 2)
			return (ret);
		if (tok->type == PIPE)
			is_cmd = 1;
		else if (tok->type == WORD)
			is_cmd = 0;
		tokens = tokens->next;
	}
	return (1);
}

int	check_args(t_list *tokens)
{
	t_token	*tok;

	if (!tokens)
		return (0);
	tok = tokens->content;
	if (tok->type == PIPE)
		return (ft_putstr_fd(
				"minishell: syntax error near unexpected token `|'\n",
				2), -2);
	return (check_tokens(tokens, tok));
}
