/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:19:57 by ssivilay          #+#    #+#             */
/*   Updated: 2026/03/23 13:25:15 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*parsed_cmds(t_list *tokens, int *exit_code)
{
	t_list	*cmd_list;
	int		ret;

	ret = check_args(tokens);
	if (ret == 1)
	{
		cmd_list = token_to_cmd(tokens);
		return (cmd_list);
	}
	if (ret == -2)
		*exit_code = 2;
	else if (ret == -1)
		*exit_code = 1;
	else
		*exit_code = 0;
	return (NULL);
}
