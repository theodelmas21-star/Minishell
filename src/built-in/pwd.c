/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:42:37 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/17 09:58:50 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int pwd(void)
{
    char *result;
    
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