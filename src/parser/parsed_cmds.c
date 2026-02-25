/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:19:57 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/25 20:32:53 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*parsed_cmds(t_list *tokens)
{
	t_list *cmd_list;

	if (check_args(tokens))
	{
		cmd_list = token_to_cmd(tokens);
		return (cmd_list);
	}
	else
		return (NULL);
}
