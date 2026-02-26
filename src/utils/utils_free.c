/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:49:35 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/26 16:29:34 by ssivilay         ###   ########.fr       */
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

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->arg);
	ft_lstclear(&token->subtokens, del_token);
	free(token);
}

void	free_list(t_list *list)
{
	t_list	*current;

	while (list)
	{
		current = list;
		list = list->next;
		del_token(current->content);
		free(current);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_redir	*cur_redir;

	if (!cmd)
		return ;
	free_tab(cmd->cmd);
	cur_redir = (t_redir *)cmd->redirs;
	while (cur_redir)
	{
		if (cur_redir && cur_redir->fd)
			close(cur_redir->fd);
		cur_redir = (t_redir *)cmd->redirs->next;
	}
}

void	free_cmds(t_list *cmds)
{
	t_list	*current;
	t_cmd	*cur_cmd;
	t_redir	*cur_redir;

	if (!cmds)
		return ;
	while (cmds)
	{
		current = cmds;
		cur_cmd = (t_cmd *)current->content;
		cur_redir = (t_redir *)cur_cmd->redirs;
		cmds = cmds->next;
		free_tab(cur_cmd->cmd);
		if (cur_redir && cur_redir->fd)
			close(cur_redir->fd);
		if (current)
			free(current);
	}
}

void	free_s_env(t_env *s_env)
{
	free_tab(s_env->path_split);
	free(s_env);
}
