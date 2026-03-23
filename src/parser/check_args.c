/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:08:01 by ssivilay          #+#    #+#             */
/*   Updated: 2026/03/23 14:33:43 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_pipe(t_token *tok, t_token *next)
{
	if (tok->type == PIPE)
	{
		if (!next)
			return (ft_putstr_fd(">\n", 2), 1);
		if (next->type == PIPE)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(next->arg, 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
	}
	return (0);
}
static int	check_redir(t_token *tok, t_token *next)
{
	if (is_redirection(tok->type))
	{
		if (!next)
			return (ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2),
				1);
		if (next->type != WORD)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(next->arg, 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
	}
	return (0);
}

static int	check_char(t_token *tok)
{
	if (ft_strlen(tok->arg) > 0)
	{
		if (ft_strncmp(tok->arg, ":", ft_strlen(tok->arg)) == 0)
			return (1);
		if (ft_strncmp(tok->arg, "!", ft_strlen(tok->arg)) == 0)
			return (2);
	}
	return (0);
}

int	check_args(t_list *tokens)
{
	t_token	*tok;
	t_token	*next;
	int		ret;

	if (!tokens)
		return (0);
	tok = tokens->content;
	next = NULL;
	if (tok->type == PIPE)
		return (ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2), -2);
	while (tokens)
	{
		tok = tokens->content;
		if (tokens->next)
			next = tokens->next->content;
		else
			next = NULL;
		ret = check_char(tok);
		if (ret == 1)
			return (0);
		if (ret == 2)
			return (-1);
		if (check_pipe(tok, next) || check_redir(tok, next))
			return (-2);
		tokens = tokens->next;
	}
	return (1);
}
