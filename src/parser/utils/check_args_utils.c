/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:28:51 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/03 13:38:36 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_pipe(t_token *tok, t_token *next)
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
int	check_redir(t_token *tok, t_token *next)
{
	if (is_redirection(tok->type))
	{
		if (!next)
			return (ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
					2), 1);
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

int	check_char(t_token *tok)
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

int	check_token(t_token *tok, t_token *next, int is_cmd)
{
	if (is_cmd && check_char(tok) == 1)
		return (0);
	if (is_cmd && check_char(tok) == 2)
		return (-1);
	if (check_pipe(tok, next) || check_redir(tok, next))
		return (-2);
	return (2);
}
