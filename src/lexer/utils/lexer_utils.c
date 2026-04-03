/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:48:55 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/03 13:24:00 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		return (REDIR_OUT);
	else
		return (WORD);
}

void	remove_dollar(t_lexer *lexer)
{
	int	len;

	len = ft_strlen(lexer->tmp);
	if (len > 0 && lexer->tmp[len - 1] == '$' && (len < 2 || lexer->tmp[len
				- 2] != '$'))
		lexer->tmp[--len] = '\0';
	if (lexer->tmp[0])
		on_create_token(lexer, NO_QUOTE, 1);
	else
	{
		free(lexer->tmp);
		lexer->tmp = NULL;
	}
}
