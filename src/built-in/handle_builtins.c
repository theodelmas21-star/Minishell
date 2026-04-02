/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:34:52 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/02 15:34:57 by ssivilay         ###   ########.fr       */
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
	t_exit_args	exit_args;

	exit_args.exit_code = 0;
	exit_args.in_pipe = 1;
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
		return (is_exit(cmd, NULL, NULL, exit_args));
	return (handle_builtins_second(cmd, s_env));
}
