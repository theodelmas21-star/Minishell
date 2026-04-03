/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:00:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 09:51:24 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exit_args init_exit_args(t_exec *exc)
{
	t_exit_args exit_args;

	exit_args.exc = exc;
	exit_args.exit_code = exc->exit_code;
	exit_args.in_pipe = 0;
	return (exit_args);
}

void close_fds_exec_builtin_cmd(t_index std)
{
		dup2(std.j, STDIN_FILENO);
		dup2(std.i, STDOUT_FILENO);
		close(std.i);
		close(std.j);
}

int	exec_builtin_cmd(t_list *cmds, t_env *s_env, t_exec exc)
{
	t_cmd		*cmd;
	int			ret;
	t_index		std;
	t_exit_args	exit_args;

	cmd = ((t_cmd *)cmds->content);
	std = (t_index){0};
	exit_args = init_exit_args(&exc);
	std.i = dup(STDOUT_FILENO);
	std.j = dup(STDIN_FILENO);
	if (apply_redirections(cmd, s_env, exc) == 1)
		return (close(std.i), close(std.j), 1);
	ret = handle_builtins(cmd, s_env, 1);
	close_fds_exec_builtin_cmd(std);
	if (ret == 1)
	{
		exit_args.exit_code = 1;
		is_exit(cmd, cmds, s_env, exit_args);
	}
	else if (is_exit(cmd, cmds, s_env, exit_args))
		ret = 1;
	if (ret == 1)
		return (1);
	return (0);
}
