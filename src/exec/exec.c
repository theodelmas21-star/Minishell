/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:35:12 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 14:38:37 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_path(t_cmd *current, t_env *env)
{
	int		is_dir;
	char	*old;

	is_dir = is_directory(current->cmd[0]);
	old = current->cmd[0];
	current->cmd[0] = find_cmd_path(env, current);
	if (current->cmd[0] != old)
		free(old);
	if (current->cmd[0] == NULL)
	{
		free(current->cmd[0]);
		if (is_dir)
			current->cmd_error = 126;
		else if (current->cmd_error == 0)
			current->cmd_error = 127;
	}
}

int	find_all_cmd_path(t_list *cmds, t_env *env)
{
	t_cmd	*current;
	t_list	*cur_cmd;

	cur_cmd = cmds;
	while (cur_cmd)
	{
		current = (t_cmd *)cur_cmd->content;
		if (current->cmd[0] == NULL)
		{
			cur_cmd = cur_cmd->next;
			continue ;
		}
		check_path(current, env);
		cur_cmd = cur_cmd->next;
	}
	return (0);
}

int	secur_fork(t_list *cmds, t_cmd *current, int pid)
{
	if (pid == -1)
	{
		if (cmds->next)
		{
			close(current->pipefd[1]);
			close(current->pipefd[0]);
		}
		return (perror("Fork error"), 1);
	}
	return (0);
}

int	exec(t_list *cmds, t_env *s_env, t_exec exc)
{
	int	status;
	int	lastpid;

	if (pipe_exec(cmds, s_env, &lastpid, &exc))
		return (1);
	waitpid(lastpid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		exc.exit_code = 128 + WTERMSIG(status);
	}
	else if (WIFSIGNALED(status))
		exc.exit_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		exc.exit_code = WEXITSTATUS(status);
	while (wait(&status) > 0)
		;
	g_signal = 0;
	return (exc.exit_code);
}

int	call_exec(t_list *cmds, t_env *s_env, t_exec exc)
{
	if (!cmds)
		return (exc.exit_code);
	if (expander(cmds, s_env, exc.exit_code))
		return (1);
	if (!cmds->next && ((t_cmd *)cmds->content)->is_builtin == 1)
	{
		find_all_cmd_path(cmds, s_env);
		return (exec_builtin_cmd(cmds, s_env, exc));
	}
	if (!cmds->next)
	{
		find_all_cmd_path(cmds, s_env);
		if (((t_cmd *)cmds->content)->cmd_error)
			return (((t_cmd *)cmds->content)->cmd_error);
	}
	else
		find_all_cmd_path(cmds, s_env);
	return (exec(cmds, s_env, exc));
}
