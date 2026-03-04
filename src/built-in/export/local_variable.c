/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:33:08 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/04 11:34:48 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int create_local(t_cmd *cmd, t_env *s_env)
{
    t_index index;
    char **new;

    index = (t_index){0};
    while (cmd->cmd[index.i])
        index.i++;
    new = malloc(sizeof(char *) * (index.i + 1));
    if (!new)
        return (1);
    while (cmd->cmd[index.j])
    {
        new[index.j] = ft_strdup(cmd->cmd[index.j]);
        if (!new[index.j])
            return (free_tab(new), 1);
        index.j++;
    }
    new[index.j] = NULL;
    s_env->local = new;
    return (0);
}

char *create_new_local(t_cmd *cmd, t_env *s_env, int len)
{
    char **new;
    t_index index;

    index = (t_index){0};
    new = malloc(sizeof(char *) * len + 1);
    if (!new)
        return (NULL);
    while (s_env->local[index.i])
    {
        new[index.i] = ft_strdup(s_env->local[index.i]);
        if (!new[index.i])
            return (free_tab(new), NULL);
        index.i++;
    }
    while (cmd->cmd[index.j])
    {
        new[index.i] = ft_strdup(cmd->cmd[index.j]);
        if (!new[index.i])
            return (free_tab(new), NULL);
        index.i++;
    }
    new[index.i] = NULL;
    return (new);
}

int add_local_variables(t_cmd *cmd, t_env *s_env)
{
    t_index index;
    char    **tmp;

    index = (t_index){0};
    if (!s_env->local)
        return (create_local(cmd, s_env));
    while (cmd->cmd[index.i])
        index.i++;
    while (s_env->local[index.j])
        index.j++;
    tmp = s_env->local;
    s_env->local = create_new_local(cmd, s_env, index.i + index.j);
    if (!s_env->local)
        return (1);
    free(tmp);
    return (0);
}
