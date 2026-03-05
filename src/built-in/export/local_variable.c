/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 10:33:08 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/05 14:49:57 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int create_local(t_cmd *cmd, t_env *s_env)
{
    t_index index;
    t_env *env;

    index = (t_index){0};
    while (cmd->cmd[index.i])
        index.i++;
    env = ((t_env *)s_env->local->content);
    if (!env)
        return (1);
    env->env = malloc(sizeof(char *) * (index.i + 1));
    if (!env->env)
        return (free(env), 1);
    while (cmd->cmd[index.j])
    {
        env->env[index.j] = ft_strdup(cmd->cmd[index.j]);
        if (!env->env[index.j])
            return (free_tab(env->env), free(env), 1);
        index.j++;
    }
    env->env[index.j] = NULL;
    ((t_env *)s_env->local->content)->env = env->env;
    printf("create_local : %s\n", ((t_env *)s_env->local->content)->env[index.j - 1]);
    return (0);
}

char **create_new_local(t_cmd *cmd, t_env *s_env, int len)
{
    char **new;
    t_index index;
    t_env *local;

    index = (t_index){0};
    new = malloc(sizeof(char *) * (len + 1));
    if (!new)
        return (NULL);
    local = (t_env *)s_env->local->content;
    while (local->env[index.i])
    {
        new[index.i] = ft_strdup(local->env[index.i]);
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
        index.j++;
    }
    new[index.i] = NULL;
    return (new);
}

int is_local_variables(t_cmd *cmd)
{
    t_index index;

    index = (t_index){0};
    while (cmd->cmd[index.i])
    {
        if (parser_export(cmd->cmd[index.i]))
            return (1);
        while (cmd->cmd[index.i][index.j] && cmd->cmd[index.i][index.j] != '=')
            index.j++;
        if (!cmd->cmd[index.i][index.j])
            return (1);
        index.i++;
    }
    return (0);
}

int add_local_variables(t_cmd *cmd, t_env *s_env)
{
    t_index index;
    t_env *env;
    char    **tmp;

    index = (t_index){0};
    if (is_local_variables(cmd) == 1)
        return (0);
    printf("hello : before create local\n");
    if (!((t_env *)s_env->local->content)->env)
        return (create_local(cmd, s_env));
    printf("hello : after create local\n");
    while (cmd->cmd[index.i])
        index.i++;
    env = ((t_env *)s_env->local->content);
    while (env->env[index.j])
        index.j++;
    tmp = env->env;
    env->env = create_new_local(cmd, s_env, index.i + index.j);
    if (!env->env)
        return (1);
    if (tmp)
        free(tmp);
    ((t_env *)s_env->local->content)->env = env->env;
    return (0);
}

int change_list_var(t_env *s_env, t_env *local, int local_idx)
{
    char **new;
    t_index index;
    char **tmp;

    index = (t_index){0};
    while (s_env->env[index.i])
        index.i++;
    new = malloc(sizeof(char *) * (index.i + 2));
    if (!new)
        return (1);
    while (s_env->env[index.j])
    {
        new[index.j] = ft_strdup(s_env->env[index.j]);
        index.j++;
    }
    new[index.j++] = local->env[local_idx];
    new[index.j] = NULL;
    tmp = s_env->env;
    s_env->env = new;
    free(tmp);
    return (0);
}
