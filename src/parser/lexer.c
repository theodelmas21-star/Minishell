/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:55:36 by ssivilay          #+#    #+#             */
/*   Updated: 2026/01/30 19:03:53 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	arg_to_token(char *buffer, t_list *tokens)
{
	char	**tab;
	t_token	*new_token;
	t_index	index;

	tokens = NULL;
	tab = ft_split(buffer, ' ');
	if (!tab)
		return ;
	index.i = 0;
	while (tab[index.i])
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
		{
			free_tab(tab);
			return ;
		}
		new_token->arg = ft_strdup(tab[index.i]);
		if (!new_token->arg)
		{
			free(new_token);
			free_tab(tab);
			return ;
		}
		new_token->type = STRING;
		ft_lstadd_back(&tokens, ft_lstnew(new_token));
		index.i++;
	}
    index.i = 0;
	printf("token = %s\n", ((t_token *)tokens->content)->arg);
	free_tab(tab);
}
