/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:49:35 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/18 10:18:48 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_list(t_list *list)
{
	t_list *current;

	while (list)
	{
		current = list;
		list = list->next;
		free(current->content);
		free(current);
	}
}

void	free_cmds(t_list *cmds)
{
	t_list *current;
	t_cmd	*cur_cmd;
	t_redir *cur_redir;

	if (!cmds)
		return ;
	while (cmds)
	{
		current = cmds;
		cur_cmd = (t_cmd *)current->content;
		cur_redir = (t_redir *)cur_cmd->redirs;
		cmds = cmds->next;
		free_tab(cur_cmd->cmd);
		/*if (cur_redir && cur_redir->fd)
			close(cur_redir->fd);
		if (current)
			free(current);*/
	}
}

void free_s_env(t_env *s_env)
{
	free_tab(s_env->path_split);
	free(s_env);
}
