/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:42:37 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/20 09:38:24 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int pwd(t_cmd *cmd)
{
    char *result;
    
    if (cmd->cmd[1])
    {
        printf("Only pwd without options or args is handled here.");
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