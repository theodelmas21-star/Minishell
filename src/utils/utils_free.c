/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:49:35 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/04 21:04:16 by tdelmas2         ###   ########.fr       */
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

void	free_all_exit(t_list *head, t_env *s_env, int res)
{
	close_all_heredoc_fds(head);
	free_cmds(head);
	free_s_env(s_env);
	exit(res);
}
