/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:49:35 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/02 17:59:49 by ssivilay         ###   ########.fr       */
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
	if (redir->target != NULL)
		free(redir->target);
	if (redir->delimiter != NULL)
		free(redir->delimiter);
	free(redir);
}

void free_tab_cmd(t_cmd *cmd)
{
	int i;

	i = 0;
	if (!cmd || !cmd->cmd)
		return ;
	while (cmd->is_expand[i] != -1)
	{
		free(cmd->cmd[i]);
		i++;
	}
	free(cmd->cmd);
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free_tab_cmd(cmd);
	free(cmd->is_expand);
	free(cmd->sub_args);
	free(cmd->quote_type);
	ft_lstclear(&cmd->redirs, free_redir);
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

void free_tab_rest_cmd(char **old, int len)
{
	int i;

	if (!old)
		return ;
	i = 0;
	while (i < len)
	{
		free(old[i]);
		i++;
	}
	free(old);
}