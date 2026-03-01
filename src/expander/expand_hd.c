/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 09:32:32 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/01 15:36:07 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *expand_hd(char *res, t_env *s_env, t_exec exc)
{
    t_cmd *tmp;
    char    *final;

    tmp = malloc(sizeof(t_cmd));
    if (!tmp)
        return NULL;
    tmp->cmd = malloc(sizeof(char *) * 2);
    if (!tmp->cmd)
        return (free(tmp), NULL);
    tmp->cmd[0] = res;
    tmp->cmd[1] = NULL;
    if (expand_cmd(tmp, s_env, exc.exit_code) == 1)
        return (free(tmp), free_tab(tmp->cmd), NULL);
    final = ft_strdup(tmp->cmd[0]);
    if (!final)
        return (free_tab(tmp->cmd), free(tmp), NULL);
    free_tab(tmp->cmd);
    free(tmp);
    return (final);
}
