/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:42:37 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/22 23:20:25 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int pwd(t_cmd *cmd)
{
    char *result;
    
    if (cmd->cmd[1])
    {
        printf("minishell: Only pwd without options or args is handled here.\n");
        return (1);
    }
    result = getcwd(NULL, 0);
    if (!result)
    {
        perror("PWD Error");
        return (1);
    }
    printf("%s\n", result);
    free(result);
    return (0);
}