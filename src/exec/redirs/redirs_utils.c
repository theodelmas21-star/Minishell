/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:32:44 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/04 18:56:33 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_input_redir(t_redir *redir_R, t_env *s_env, t_exec exc)
{
	int	fd;

	if (redir_R->type == REDIR_HEREDOC)
	{
		if (redir_R->fd != -1)
			fd = redir_R->fd;
		else
		{
			if (hd_manage(redir_R, s_env, exc) != 0)
				return (1);
			fd = open("/tmp/minishell_hd", O_RDONLY);
		}
	}
	else
		fd = open(redir_R->target, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("minishell: ", 2), perror(redir_R->target), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (redir_R->type == REDIR_HEREDOC)
		unlink("tmp");
	return (0);
}

int	handle_output_redir(t_redir *redir_R)
{
	int	fd;

	fd = open(redir_R->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror(redir_R->target), 1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	handle_append_redir(t_redir *redir_R)
{
	int	fd;

	fd = open(redir_R->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (perror(redir_R->target), 1);
	return (dup2(fd, STDOUT_FILENO), close(fd), 0);
}

int	apply_all_redirs(t_redir redir_R, t_env *s_env, t_exec exc)
{
	if (redir_R.type == REDIR_IN || redir_R.type == REDIR_HEREDOC)
	{
		if (handle_input_redir(&redir_R, s_env, exc) != 0)
			return (1);
	}
	else if (redir_R.type == REDIR_OUT)
	{
		if (handle_output_redir(&redir_R) != 0)
			return (1);
	}
	else if (redir_R.type == REDIR_APPEND)
	{
		if (handle_append_redir(&redir_R) != 0)
			return (1);
	}
	return (0);
}
