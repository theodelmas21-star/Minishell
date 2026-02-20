/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:13:05 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/20 11:54:25 by tdelmas2         ###   ########.fr       */
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
    t_index index;
    int option;

    index = (t_index){0, 1, 0};
    while (cmd->cmd[index.j] && cmd->cmd[index.j][index.i] == '-')
        index.i = is_n(cmd->cmd[1]);
    option = index.i;
    while (cmd->cmd[++index.i])
    {
        if (cmd->cmd[index.i + 1])
            printf("%s ", cmd->cmd[index.i]);
        else
            printf("%s", cmd->cmd[index.i]);
    }
    if (option == 0)
        printf("\n");
    return (0);
}

//a refaire pour gerer -nnn -nnn salut
