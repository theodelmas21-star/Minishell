/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 09:32:32 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/02 10:23:32 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *add_newline(char *res)
{
    t_index index;
    char    *new;

    index = (t_index){0};
    new = malloc(sizeof(char) * (ft_strlen(res) + 2));
    if (!new)
        return (free(res), NULL);
    while (res[index.i])
    {
        new[index.i] = res[index.i];
        index.i++;
    }
    new[index.i++] = '\n';
    new[index.i] = '\0';
    return (free(res), new);
}

char *r_newline(char *res)
{
    t_index index;
    char    *new;

    index = (t_index){0};
    new = malloc(sizeof(char) * ft_strlen(res));
    if (!new)
        return (free(res), NULL);
    while (res[index.i] && res[index.i] != '\n')
    {
        new[index.i] = res[index.i];
        index.i++;
    }
    new[index.i] = '\0';
    return (free(res), new);
}

t_cmd *init_tmp(char *res)
{
    t_cmd *tmp;
    
    res = r_newline(res);
    if (!res)
        return NULL;
    tmp = malloc(sizeof(t_cmd));
    if (!tmp)
        return NULL;
    tmp->cmd = malloc(sizeof(char *) * 2);
    if (!tmp->cmd)
        return (free(tmp), NULL);
    tmp->cmd[0] = res;
    tmp->cmd[1] = NULL;
    tmp->is_expand = malloc(sizeof(int) * 1);
    tmp->is_expand[0] = 1;
    return (tmp);
}

char *expand_hd(char *res, t_env *s_env, t_exec exc)
{
    t_cmd *tmp;
    char    *final;

    tmp = init_tmp(res);
    if (expand_cmd(tmp, s_env, exc.exit_code) == 1)
        return (free(tmp), free_tab(tmp->cmd), NULL);
    tmp->cmd[0] = add_newline(tmp->cmd[0]);
    if (!tmp->cmd[0])
        return (free(tmp), free_tab(tmp->cmd), NULL);
    final = ft_strdup(tmp->cmd[0]);
    if (!final)
        return (free_tab(tmp->cmd), free(tmp), NULL);
    free_tab(tmp->cmd);
    free(tmp);
    return (final);
}
