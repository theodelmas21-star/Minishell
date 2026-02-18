/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:13:05 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/17 10:17:16 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_n(char *option)
{
    int i;

    i = 1;
    while (option[i])
    {
        if (option [i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int    echo(t_cmd *cmd)
{
    int i;
    int option;

    i = 0;
    if (!cmd->cmd || ft_strncmp(cmd->cmd[0], "echo", 4) != 0)
        return (1);
    if (cmd->cmd[1][i] == '-')
        i = is_n(cmd->cmd[1]);
    option = i;
    while (cmd->cmd[++i])
        printf("%s", cmd->cmd[i]);
    if (option == 0)
        printf("\n");
    return (0);
}
