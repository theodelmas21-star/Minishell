/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:38:41 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/18 10:42:05 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}

int size_cmd(t_list *cmds)
{
    t_list *s_list;
	int		size;
	
	size = 0;
    s_list = cmds;
	if (!cmds)
		return (0);
	while (s_list)
	{
        size++;
		s_list = s_list->next;
	}
	return (size);
}
