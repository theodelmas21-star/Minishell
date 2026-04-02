/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 15:32:44 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/02 11:59:15 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	hd_manage(t_redir *redir_R, t_env *s_env, t_exec exc)
{
	char	*tmp;

	redir_R->fd = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir_R->fd < 0)
		return (perror("Open error"), 1);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 2);
		tmp = get_next_line(0);
		if (!tmp)
			return (free(tmp), get_next_line(-1), close(redir_R->fd), 0);
		if (ft_strncmp(tmp, redir_R->delimiter, ft_strlen(redir_R->delimiter)) == 0
				&& (tmp[ft_strlen(redir_R->delimiter)] == '\n'
				|| tmp[ft_strlen(redir_R->delimiter)] == '\0'))
			return (free(tmp), get_next_line(-1), close(redir_R->fd), 0);
		if (redir_R->exp_hd)
		{
			tmp = expand_hd(tmp, s_env, &exc, 1);
			if (!tmp && exc.error == 1)
				return (1);
		}
		ft_putstr_fd(tmp, redir_R->fd);
		free(tmp);
	}
}

int	handle_input_redir(t_redir *redir_R, t_env *s_env, t_exec exc)
{
	int	fd;

	if (redir_R->type == REDIR_HEREDOC)
	{
		if (hd_manage(redir_R, s_env, exc) != 0)
			return (1);
		fd = open("tmp", O_RDONLY);
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
