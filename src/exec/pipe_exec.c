/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 09:20:37 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/04 20:02:03 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_child(t_cmd *current, t_list *head, t_env *s_env, t_exec *exc)
{
	t_exit_args	args;
	int			res;

	if (current->is_builtin == 1)
	{
		if (ft_strncmp(current->cmd[0], "exit", 5) == 0)
		{
			args.exc = exc;
			args.exit_code = 0;
			args.in_pipe = 1;
			is_exit(current, head, s_env, args);
		}
		res = handle_builtins(current, s_env, 0);
		free_all_exit(head, s_env, res);
	}
}

void	start_child(t_exec *exc)
{
	reset_signals();
	close(exc->saved_stdin);
	close(exc->saved_stdout);
}

void	child_exec(t_list *cmds, t_env *s_env, t_exec *exc, t_list *head)
{
	t_cmd	*current;

	current = ((t_cmd *)cmds->content);
	start_child(exc);
	close_heredoc_fds(head, cmds);
	if (exc->prev_fd != -1)
	{
		dup2(exc->prev_fd, STDIN_FILENO);
		close(exc->prev_fd);
	}
	if (cmds->next)
	{
		close(current->pipefd[0]);
		dup2(current->pipefd[1], STDOUT_FILENO);
		close(current->pipefd[1]);
	}
	if (apply_redirections(current, s_env, *exc) != 0)
		free_all_exit(head, s_env, 1);
	builtin_child(current, head, s_env, exc);
	if (current->cmd[0] == NULL)
		free_all_exit(head, s_env, current->cmd_error);
	else
		execve(current->cmd[0], current->cmd, s_env->env);
	perror("Execve error");
	free_all_exit(head, s_env, 1);
}

void	close_fds(t_list *cmds, t_exec *exc, t_cmd *current)
{
	if (cmds->next)
	{
		close(current->pipefd[1]);
		if (exc->prev_fd != -1)
			close(exc->prev_fd);
		exc->prev_fd = current->pipefd[0];
	}
	else if (exc->prev_fd != -1)
		close(exc->prev_fd);
}

int	pipe_exec(t_list *cmds, t_env *s_env, int *pid, t_exec *exc)
{
	t_cmd	*current;
	t_list	*head;

	if (!cmds)
		return (0);
	head = cmds;
	exc->prev_fd = -1;
	while (cmds)
	{
		current = ((t_cmd *)cmds->content);
		if (cmds->next)
			pipe(current->pipefd);
		g_signal = -1;
		*pid = fork();
		if (secur_fork(cmds, current, *pid))
			return (1);
		if (*pid == 0)
			child_exec(cmds, s_env, exc, head);
		close_fds(cmds, exc, current);
		cmds = cmds->next;
	}
	return (0);
}
