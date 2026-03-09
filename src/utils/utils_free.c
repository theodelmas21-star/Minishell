/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:49:35 by ssivilay          #+#    #+#             */
/*   Updated: 2026/03/09 15:10:48 by ssivilay         ###   ########.fr       */
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

	if (!cmds)
		return ;
	while (cmds)
	{
		current = cmds;
		cur_cmd = (t_cmd *)current->content;
		cmds = cmds->next;
		if (cur_cmd->redirs)
        	free_list(cur_cmd->redirs);
		free_tab(cur_cmd->cmd);
		/* if (cur_redir && cur_redir->fd)
			close(cur_redir->fd); */
		if (current)
			free(current);
	}
}

void	free_s_env(t_env *s_env)
{
	if (!s_env)
		return ;
	if (s_env->path_split)
		free_tab(s_env->path_split);
	if (s_env->env)
		free_tab(s_env->env);
	free(s_env);
}
