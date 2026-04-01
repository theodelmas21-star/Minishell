/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:34:52 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/01 10:07:17 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_builtins_second(t_cmd *cmd, t_env *s_env)
{
	if (ft_strncmp(cmd->cmd[0], "export", 8) == 0)
		return (export(cmd, s_env));
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		return (pwd(cmd));
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		return (unset(cmd, s_env));
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		return (cd(cmd, s_env));
	return (0);
}

int	handle_builtins(t_cmd *cmd, t_env *s_env, int pid)
{
	if (!cmd || !cmd->cmd[0])
		return (1);
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		return (echo(cmd));
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
	{
		if (cmd->cmd[1])
		{
			printf("Only env without options or args is handled here.\n");
			return (1);
		}
		return (env(s_env));
	}
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0 && pid == 0)
		return (is_exit(cmd, NULL, NULL, 0, 1));
	return (handle_builtins_second(cmd, s_env));
}
