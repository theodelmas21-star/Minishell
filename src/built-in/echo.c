/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 11:13:05 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/05 09:34:46 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    echo(t_cmd *cmd)
{
    t_index     index;

    index.i = 0;
    index.j = 1;
    index.k = 2;
    if (!cmd->argv || ft_strncmp(cmd->argv[0], "echo", 4))
        return ;
    if (cmd->argv[1][index.i] == '-')
    {
        index.i++;
        while (cmd->argv[1][index.i])
        {
            if (cmd->argv[1][index.i++] != 'n')
                index.j--;
        }
    }
    else
        index.j--;
    if (index.j == 0)
        printf("%s", cmd->argv[1]);
    while (cmd->argv[index.k])
        printf("%s",cmd->argv[index.k++]);
    if (index.j == 0)
        printf("'\n");
}
