/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:00:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/02 13:34:33 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin_cmd(t_list *cmds, t_env *s_env, t_exec exc)
{
	t_cmd	*cmd;
	int		ret;
	t_index	std;

	cmd = ((t_cmd *)cmds->content);
	std = (t_index){0};
	std.i = dup(STDOUT_FILENO);
	std.j = dup(STDIN_FILENO);
	if (apply_redirections(cmd, s_env, exc) == 1)
		return (close(std.i), close(std.j), 1);
	ret = handle_builtins(cmd, s_env, 1);
	dup2(std.j, STDIN_FILENO);
	dup2(std.i, STDOUT_FILENO);
	close(std.i);
	close(std.j);
	if (ret == 1)
		is_exit(cmds, s_env, exc, 1, 0);
	else if (is_exit(cmds, s_env, exc, exc.exit_code, 0))
		ret = 1;
	if (ret == 1)
		return (1);
	return (0);
}
