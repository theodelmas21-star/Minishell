/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:34:43 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/20 10:57:59 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int parser_export(char *cmd)
{
    t_index index;
    
    index = (t_index){0};
    if (!ft_strchr(cmd, '='))
            return (1);
    if ((cmd[index.i] < 'a' || cmd[index.i] > 'z') && 
        (cmd[index.i] < 'A' || cmd[index.i] > 'Z') && cmd[index.i] != '_')
        return (1);
    while (cmd[index.i])
    {
        if ((cmd[index.i] < 'a' || cmd[index.i] > 'z') && 
        (cmd[index.i] < 'A' || cmd[index.i] > 'Z') && cmd[index.i] != '_'
        && (cmd[index.i] < '0' || cmd[index.i] > '9'))
            return (1);
    }
    return (0);
}

int is_var(char *var, char **env)
{
    t_index index;
    
    index.k = 0;
    index.j = 0;
    while (env[index.j])
    {
        if (ft_strncmp(var, env[index.j], index.k) == 0)
            return (index.j);
        index.j++;
    }
    return (-1);
}

int create_var(char *var, t_env *s_env)
{
    char    **new_env;
    char    **tmp;
    t_index index;

    index.i = 0;
    while (s_env->env[index.i])
        index.i++;
    new_env = malloc(sizeof(char *) * (index.i + 2));
    if (!new_env)
        return (1);
    index.i = 0;
    while (s_env->env[index.i])
        new_env[index.i] = s_env->env[index.i++];
    new_env[index.i] = var;
    new_env[index.i] = NULL;
    tmp = s_env->env;
    s_env->env = new_env;
    free_tab(tmp);
    return (0);
}

int export_options(t_cmd *cmd, t_env *s_env)
{
    t_index index;

    index.i = 1;
    while (cmd->cmd[index.i])
    {
        index.j = 0;
        if (parser_export(cmd->cmd[index.i]) == 1)
        {
            printf("minishell : %s: not a valid identifier", cmd->cmd[index.i]);
            index.i++;
            if (!cmd->cmd[index.i])
                return (1);
        }
        index.k = is_var(cmd->cmd[index.i], s_env->env);
        if (concat_or_replace(index, cmd, s_env) == 1)
            return (1);
        else if (index.k == -1 && create_var(cmd->cmd[index.i], s_env) == 1)
            return (1);
    }
    return (0);
}

int export(t_cmd *cmd, t_env *s_env)
{
    if (!cmd || !s_env)
        return (1);
    if (!cmd->cmd[1])
        return (simple_export(s_env));
    return (export_options(cmd, s_env));
}