/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 18:56:18 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/04 19:09:07 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	on_error(t_redir *redir_R)
{
	get_next_line(-1);
	close(redir_R->fd);
	if (g_signal)
		return (1);
	write(2, "\n", 1);
	ft_putstr_fd("minishell: warning: "
		"here-document delimited by end-of-file (wanted `",
		2);
	ft_putstr_fd(redir_R->delimiter, 2);
	ft_putstr_fd("')\n", 2);
	return (0);
}

int	hd_manage(t_redir *redir_R, t_env *s_env, t_exec exc)
{
	char	*tmp;

	redir_R->fd = open("/tmp/minishell_hd", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir_R->fd < 0)
		return (perror("Open error"), 1);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 2);
		tmp = get_next_line(0);
		if (!tmp)
			return (free(tmp), on_error(redir_R));
		if (stop_hd(tmp, redir_R))
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
