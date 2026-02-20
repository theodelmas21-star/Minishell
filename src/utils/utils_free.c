/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:49:35 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/19 17:55:41 by ssivilay         ###   ########.fr       */
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
	t_list	*current;

	while (list)
	{
		current = list;
		list = list->next;
		free(current);
	}
}

void	free_cmds(t_list *cmds)
{
	t_list	*current;
	t_cmd	*cur_cmd;

	while (cmds)
	{
		current = cmds;
		cur_cmd = (t_cmd *)current->content;
		cmds = cmds->next;
		free_tab(cur_cmd->cmd);
		free(current);
	}
}

void	del_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->arg);
	ft_lstclear(&token->subtokens, del_token);
	free(token);
}
