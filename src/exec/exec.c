/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:35:12 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/11 09:30:07 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}

void fork_exec(t_cmd *cmd, char **envp, int fd_in, int fd_out)
{
    int     pid;
    int     status;

    pid = fork();
    if (pid < 0)
        return (free_tab(cmd->cmd), close(fd_in), close(fd_out), error("Fork error"));
    if (pid == 0)
    {
        /*dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);*/
		execve(cmd->cmd[0], cmd->cmd, envp);
		return (free_tab(cmd->cmd), error("Execve error"));
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            return (free_tab(cmd->cmd), error("Command execution failed"));
    }
}

void call_exec(t_list *cmds, char **envp)
{
    t_env *s_env;
    t_cmd *cmd;

    s_env = malloc(sizeof(t_env));
    if (!envp)
        return ;
    s_env->env = envp;
    s_env = find_path(s_env);
    if (!s_env->path)
        return (free(s_env));
    while (cmds)
    {
        cmd = (t_cmd *)cmds->content;
        cmd->cmd[0] = find_cmd_path(s_env, cmd);
        if (!cmd->cmd[0])
            return (free_tab(cmd->cmd), free(s_env->path), free(s_env));
        fork_exec(cmd, envp, STDIN_FILENO, STDOUT_FILENO);
        cmds = cmds->next;
    }
}
