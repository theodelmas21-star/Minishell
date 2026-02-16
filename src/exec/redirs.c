/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:17:01 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/15 17:35:58 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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