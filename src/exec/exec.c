/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:35:12 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/17 09:38:20 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    child_exec(t_list *cmds, char **envp, int prev_fd, int pid)
{
    t_cmd *current;

    current = ((t_cmd *)cmds->content);
    if (pid == 0)
    {
        if (prev_fd != -1)
        {
            dup2(prev_fd, STDIN_FILENO);
            close(prev_fd);
        }
        if (cmds->next)
        {
            dup2(current->pipefd[1], STDOUT_FILENO);
            close(current->pipefd[1]);
        }
        apply_redirections(current);
        handle_builtin_child(cmds, envp);
        execve(current->cmd[0], current->cmd, envp);
        return (free_tab(current->cmd), error("Execve error"));
    }
    if (prev_fd != -1)
        close(prev_fd);
}

void secur_fork(t_list *cmds, t_cmd *current, int pid)
{
    if (pid == -1)
    {
        if (cmds->next)
        {
            close(current->pipefd[1]);
            close(current->pipefd[0]);
        }
        return (free_cmds(cmds), error("Fork error"));
    }
}

void    pipe_exec(t_list *cmds, char **envp, int *pid)
{
    int prev_fd;
    t_cmd *current;

    if (!cmds)
        return ;
    prev_fd = -1;
    while (cmds)
    {
        current = ((t_cmd *)cmds->content);
        if (cmds->next)
            pipe(current->pipefd);
        *pid = fork();
        secur_fork(cmds, current, *pid);
        if (pid == 0 && cmds->next)
            close(current->pipefd[0]);
        child_exec(cmds, envp, prev_fd, *pid);
        if (cmds->next)
        {
            close(current->pipefd[1]);
            prev_fd = current->pipefd[0];
        }
        cmds = cmds->next;
    }
}

int find_all_cmd_path(t_list *cmds, t_env *env)
{
    t_cmd *current;
    t_list *cur_cmd;

    cur_cmd = cmds;
    while (cur_cmd)
    {
        current = (t_cmd *)cur_cmd->content;
        current->cmd[0] = find_cmd_path(env, current);
        if (!current->cmd[0])
            return (1);
        cur_cmd = cur_cmd->next;
    }
    return (0);
}

int call_exec(t_list *cmds, char **envp)
{
    t_env *s_env;
    int status;
    int lastpid;
    int exit_code;

    s_env = malloc(sizeof(t_env));
    if (!envp)
        return (1);
    s_env->env = envp;
    s_env = find_path(s_env);
    if (!s_env->path)
        return (free_s_env(s_env), free_cmds(cmds), -1);
    if (find_all_cmd_path(cmds, s_env) == 1)
        return (free_s_env(s_env), free_cmds(cmds), -1);
    if (!cmds->next && ((t_cmd *)cmds->content)->is_builtin == 1)
        handle_builtin_parent(cmds);
    else
    {
        pipe_exec(cmds, envp, &lastpid);
        waitpid(lastpid, &status, 0);
        if (WIFEXITED(status))
            exit_code = WEXITSTATUS(status);
        else
            exit_code = 1;
        while (wait(&status) > 0)
            ;
    }
    return (free_cmds(cmds), free_s_env(s_env), exit_code);
}
