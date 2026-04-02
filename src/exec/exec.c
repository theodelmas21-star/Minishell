/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:35:12 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/02 17:38:19 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_all_cmd_path(t_list *cmds, t_env *env)
{
	t_cmd	*current;
	t_list	*cur_cmd;
	int		is_dir;
	char	*old;
	int		i;

	cur_cmd = cmds;
	print_cmds(cmds);
	while (cur_cmd)
	{
		current = (t_cmd *)cur_cmd->content;
		if (current->cmd[0] == NULL)
		{
			cur_cmd = cur_cmd->next;
			continue ;
		}
		is_dir = is_directory(current->cmd[0]);
		old = current->cmd[0];
		current->cmd[0] = find_cmd_path(env, current);
		if (current->cmd[0] != old)
		{
			printf("freeing %s\n", old);
			free(old);
		}
		if (current->cmd[0] == NULL)
		{
			i = 1;
			/*while (current->cmd[i])
			{
				printf("On free : '%s'\n", current->cmd[i]);
				free(current->cmd[i]);
				current->cmd[i] = NULL;
				i++;
				printf("On s'arrete: '%s'\n", current->cmd[i]);
			}*/
			free(current->cmd[0]);
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
		return (perror("Fork error"), 1);
	}
	return (0);
}

void	child_exec(t_list *cmds, t_env *s_env, t_exec *exc, t_list *head)
{
	t_cmd		*current;
	int			res;
	t_exit_args	args;

	current = ((t_cmd *)cmds->content);
	res = 0;
	reset_signals();
	close(exc->saved_stdin);
	close(exc->saved_stdout);
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
	{
		free_cmds(head);
		free_s_env(s_env);
		exit(1);
	}
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
		free_cmds(head);
		free_s_env(s_env);
		exit(res);
	}
	else if (current->cmd[0] == NULL)
	{
		res = current->cmd_error;
		free_cmds(head);
		free_s_env(s_env);
		exit(res);
	}
	else
	{
		execve(current->cmd[0], current->cmd, s_env->env);
	}
	free_cmds(head);
	free_s_env(s_env);
	perror("Execve error");
	exit(1);
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
		if (cmds->next)
		{
			close(current->pipefd[1]);
			if (exc->prev_fd != -1)
				close(exc->prev_fd);
			exc->prev_fd = current->pipefd[0];
		}
		else if (exc->prev_fd != -1)
			close(exc->prev_fd);
		cmds = cmds->next;
	}
	return (0);
}

int	call_exec(t_list *cmds, t_env *s_env, t_exec exc)
{
	int	status;
	int	lastpid;

	// int	stdin;
	/*int	stdout;
	int	redir_res;*/
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
		/*stdout = dup(STDOUT_FILENO);
		stdin = dup(STDIN_FILENO);
		redir_res = apply_redirections(((t_cmd *)cmds->content), s_env, exc);
		dup2(stdin, STDIN_FILENO);
		dup2(stdout, STDOUT_FILENO);
		close(stdout);
		close(stdin);
		if (redir_res != 0)
			return (1);*/
		find_all_cmd_path(cmds, s_env);
		if (((t_cmd *)cmds->content)->cmd_error)
			return (((t_cmd *)cmds->content)->cmd_error);
	}
	else
		find_all_cmd_path(cmds, s_env);
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
