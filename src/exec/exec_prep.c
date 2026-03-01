/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:00:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/01 15:54:50 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prep_exec(t_list *cmds, t_env *s_env)
{
	if (!s_env->path)
		return (free_s_env(s_env), free_cmds(cmds), 1);
	if (find_all_cmd_path(cmds, s_env) == 1)
		return (free_s_env(s_env), free_cmds(cmds), 1);
	return (0);
}

int	exec_builtin_cmd(t_list *cmds, t_env *s_env, t_exec exc)
{
	t_cmd	*cmd;
	int		ret;

	cmd = ((t_cmd *)cmds->content);
	if (apply_redirections(cmd, s_env, exc) == 1)
		return (free_s_env(s_env), free_cmds(cmds), 1);
	ret = handle_builtins(cmd, s_env, 1);
	if (ret == 1)
		is_exit(cmds, s_env, 1);
	else
		is_exit(cmds, s_env, exc.exit_code);
	free_cmds(cmds);
	if (ret == 1)
		return (1);
	return (0);
}
