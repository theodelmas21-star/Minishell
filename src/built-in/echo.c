/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:13:05 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/15 15:01:01 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_n(char *option)
{
	int	i;

	i = 0;
	if (option[i] == '-')
		i++;
	else
		return (0);
	while (option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_cmd *cmd)
{
	t_index	index;
	int		option;

    index = (t_index){0, 1, 0};
    option = 0;
    while (cmd->cmd[index.j])
    {
        if (is_n(cmd->cmd[index.j]) == 1)
            option = 1;
        else
            break;
        index.j++;
    }
    while (cmd->cmd[index.j])
    {
        if (cmd->cmd[index.j][0] != '\0' &&cmd->cmd[index.j + 1])
            printf("%s ", cmd->cmd[index.j]);
        else
            printf("%s", cmd->cmd[index.j]);
        index.j++;
    }
    if (option == 0)
        printf("\n");
    return (0);
}

// a refaire pour gerer -nnn -nnn salut
