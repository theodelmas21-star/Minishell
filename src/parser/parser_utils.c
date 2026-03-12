/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:35:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/10 15:28:06 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND
		|| type == REDIR_HEREDOC)
		return (1);
	else
		return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0 || ft_strncmp(cmd, "cd",
			ft_strlen(cmd)) == 0 || ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0
		|| ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0 || ft_strncmp(cmd,
			"unset", ft_strlen(cmd)) == 0 || ft_strncmp(cmd, "env",
			ft_strlen(cmd)) == 0 || ft_strncmp(cmd, "exit",
			ft_strlen(cmd)) == 0)
		return (1);
	return (0);
}
