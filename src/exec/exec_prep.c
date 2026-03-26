/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 16:00:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/26 14:40:40 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin_cmd(t_list *cmds, t_env *s_env, t_exec exc)
{
	t_cmd	*cmd;
	int		ret;
	t_index	index;

	cmd = ((t_cmd *)cmds->content);
	index = (t_index){0};
	index.i = dup(STDOUT_FILENO);
	index.j = dup(STDIN_FILENO);
	if (apply_redirections(cmd, s_env, exc) == 1)
		return (1);
	ret = handle_builtins(cmd, s_env, 1);
	if (ret == 1)
		is_exit(cmd, cmds, s_env, 1, 0);
	else if (is_exit(cmd, cmds, s_env, exc.exit_code, 0))
		ret = 1;
	//free_cmds(cmds);
	dup2(index.j, STDIN_FILENO);
	dup2(index.i, STDOUT_FILENO);
	if (ret == 1)
		return (1);
	return (0);
}
