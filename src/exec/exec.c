/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:35:12 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/15 16:42:13 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}

void redirections(t_redir *redir_R)
{
    int fd;
    
    if (redir_R->type == REDIR_HEREDOC)
    {
        dup2(redir_R->fd, STDIN_FILENO);
        close(redir_R->fd);
    }
    if (redir_R->type == REDIR_IN)
    {
        fd = open(redir_R->target, O_RDONLY);
        if (fd < 0)
            error("Open Error");
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    if (redir_R->type == REDIR_OUT)
    {
        fd = open(redir_R->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0)
            error("Open Error");
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void apply_redirections(t_cmd *cmds)
{
    int fd;
    t_list *R;
    t_redir *redir_R;

    if (!cmds || !cmds->redirs)
        return ;
    R = cmds->redirs;
    while (R)
    {
        redir_R = ((t_redir *)R->content);
        if (redir_R->type == REDIR_APPEND)
        {
            fd = open(redir_R->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd < 0)
                error("Open Error");
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        redirections(redir_R);
        R = R->next;
    }
}

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
            return (free_cmds(cmds), 1);
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
    pipe_exec(cmds, envp, &lastpid);
    waitpid(lastpid, &status, 0);
    if (WIFEXITED(status))
        exit_code = WEXITSTATUS(status);
    else
        exit_code = 1;
    while (wait(&status) > 0)
        ;
    return (free_cmds(cmds), free_s_env(s_env), exit_code);
}
