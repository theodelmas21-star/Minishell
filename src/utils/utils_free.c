/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:49:35 by ssivilay          #+#    #+#             */
/*   Updated: 2026/03/12 09:03:30 by tdelmas2         ###   ########.fr       */
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

void	free_redir(void *content)
{
	t_redir *redir;

	redir = (t_redir *)content;
	if (!redir)
		return ;
	if (redir->target)
		free(redir->target);
	if (redir->delimiter)
		free(redir->delimiter);
	free(redir);
}

void	free_cmd(t_cmd *cmd)
{
	t_list	*cur_redir;

	if (!cmd)
		return ;
	free_tab(cmd->cmd);
	cur_redir = cmd->redirs;
	while (cur_redir)
	{
		if (cur_redir->content)
			free_redir(cur_redir->content);
		cur_redir = cur_redir->next;
	}
	ft_lstclear(&cmd->redirs, free_redir);
	free(cmd->is_expand);
	free(cmd);
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
		free_cmd(cur_cmd);
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
