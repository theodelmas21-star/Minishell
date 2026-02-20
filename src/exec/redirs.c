/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 17:17:01 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/16 11:53:34 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void hd_manage(t_redir *redir_R)
{
	char *tmp;
	
	redir_R->fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir_R->fd < 0)
		return (error("Open error"),free(redir_R->LIMITER));
	while (redir_R->fd > 0)
	{
		ft_putstr_fd("heredoc> ", 1);
		tmp = get_next_line(0);
		if (!tmp)
			break ;
		if (ft_strncmp(tmp, redir_R->LIMITER, ft_strlen(redir_R->LIMITER)) == 0)
		{
			free(tmp);
			break;
		}
		ft_putstr_fd(tmp, redir_R->fd);
		free(tmp);
	}
	get_next_line(-1);
    close(redir_R->fd);
}

void redirections(t_redir *redir_R)
{
    int fd;
    
    if (redir_R->type == REDIR_HEREDOC)
    {
        hd_manage(redir_R);
        fd = open("tmp", O_RDONLY);
        if (fd < 0)
            error("Open Error");
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
