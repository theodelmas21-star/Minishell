/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 09:35:12 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/05 13:19:56 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        return (ft_free_all(cmd->cmd), close(fd_in), error("Fork error"));
    if (pid == 0)
    {
        dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		execve(cmd->cmd[0], cmd->cmd, envp);
		return (ft_free_all(cmd->cmd), error("Execve error"));
    }
}

void call_exec(t_list *cmds, t_env *envp)
{
    
}
