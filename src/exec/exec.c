/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:35:12 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/29 12:21:23 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_all_cmd_path(t_list *cmds, t_env *env)
{
	t_cmd	*current;
	t_list	*cur_cmd;
	int		is_dir;

	cur_cmd = cmds;
	while (cur_cmd)
	{
		current = (t_cmd *)cur_cmd->content;
		if (current->cmd[0] == NULL)
		{
			cur_cmd = cur_cmd->next;
			continue ;
		}
		is_dir = is_directory(current->cmd[0]);
		current->cmd[0] = find_cmd_path(env, current);
		if (current->cmd[0] == NULL)
		{
			if (is_dir)
				current->cmd_error = 126;
			else if (current->cmd_error == 0)
				current->cmd_error = 127;
		}
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
		return (free_cmds(cmds), error("Fork error"), 1);
	}
	return (0);
}

void	child_exec(t_list *cmds, t_env *s_env, t_exec exc, int pid)
{
	t_cmd	*current;

	current = ((t_cmd *)cmds->content);
	if (pid != 0)
		return ;
	reset_signals();
	if (exc.prev_fd != -1)
	{
		dup2(exc.prev_fd, STDIN_FILENO);
		close(exc.prev_fd);
	}
	if (cmds->next)
	{
		close(current->pipefd[0]);
		dup2(current->pipefd[1], STDOUT_FILENO);
		close(current->pipefd[1]);
	}
	if (apply_redirections(current, s_env, exc) != 0)
		exit(1);
	if (current->is_builtin == 1 && handle_builtins(current, s_env, 0) == 1)
		return (exit(1));
	if (current->cmd[0] == NULL)
		exit(current->cmd_error);
	execve(current->cmd[0], current->cmd, s_env->env);
}

void	pipe_exec(t_list *cmds, t_env *s_env, int *pid)
{
	t_exec	exc;
	t_cmd	*current;

	if (!cmds)
		return ;
	exc.prev_fd = -1;
	while (cmds)
	{
		current = ((t_cmd *)cmds->content);
		if (cmds->next)
			pipe(current->pipefd);
		g_signal = -1;
		*pid = fork();
		if (secur_fork(cmds, current, *pid))
			return ;
		child_exec(cmds, s_env, exc, *pid);
		if (cmds->next)
		{
			close(current->pipefd[1]);
			if (exc.prev_fd != -1)
				close(exc.prev_fd);
			exc.prev_fd = current->pipefd[0];
		}
		else if (exc.prev_fd != -1)
			close(exc.prev_fd);
		cmds = cmds->next;
	}
}

int	call_exec(t_list *cmds, t_env *s_env, t_exec exc)
{
	int	status;
	int	lastpid;
	int	stdout;
	int	stdin;

	if (!cmds)
		return (exc.exit_code);
	if (expander(cmds, s_env, exc.exit_code))
		return (1);
	find_all_cmd_path(cmds, s_env);
	if (!cmds->next && ((t_cmd *)cmds->content)->cmd_error)
	{
		stdout = dup(STDOUT_FILENO);
		stdin = dup(STDIN_FILENO);
		apply_redirections(((t_cmd *)cmds->content), s_env, exc);
		dup2(stdin, STDIN_FILENO);
		dup2(stdout, STDOUT_FILENO);
		close(stdout);
		close(stdin);
		return (((t_cmd *)cmds->content)->cmd_error);
	}
	if (!cmds->next && ((t_cmd *)cmds->content)->is_builtin == 1)
		return (exec_builtin_cmd(cmds, s_env, exc));
	pipe_exec(cmds, s_env, &lastpid);
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
	// free_cmds(cmds);
	return (exc.exit_code);
}
