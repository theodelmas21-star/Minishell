/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:34:43 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/02 14:46:38 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int parser_export(char *cmd)
{
    int i;
    
    i = 0;
    if ((cmd[i] < 'a' || cmd[i] > 'z') && 
        (cmd[i] < 'A' || cmd[i] > 'Z') && cmd[i] != '_')
        return (1);
    while (cmd[i] && cmd[i] != '=')
    {
        if ((cmd[i] < 'a' || cmd[i] > 'z') && 
            (cmd[i] < 'A' || cmd[i] > 'Z') && cmd[i] != '_'
            && (cmd[i] < '0' || cmd[i] > '9') && cmd[i] != '+')
            return (1);
        i++;
    }
    return (0);
}

int is_var(char *var, char **env)
{
    t_index index;
    char    *eq_pos;
    int     var_len;
    int     plus_pos;
    
    index.j = 0;
    eq_pos = ft_strchr(var, '=');
    var_len = 0;
    plus_pos = -1;
    
    if (eq_pos)
    {
        plus_pos = 0;
        while (var[plus_pos] && var[plus_pos] != '=')
        {
            if (var[plus_pos] == '+' && var[plus_pos + 1] == '=')
                break ;
            plus_pos++;
        }
        var_len = plus_pos;
    }
    else
        var_len = ft_strlen(var);
    while (env[index.j])
    {
        if (ft_strncmp(var, env[index.j], var_len) == 0 && (env[index.j][var_len] == '='))
            return (index.j);
        index.j++;
    }
    return (-1);
}

char **core_create_var(char *var, t_env *s_env, int count)
{
    char    **new_env;
    int i;

    i = 0;
    new_env = malloc(sizeof(char *) * (count + 2));
    if (!new_env)
        return (NULL);
    while (i < count)
    {
        new_env[i] = ft_strdup(s_env->env[i]);
        if (!new_env[i])
        {
            free_tab(new_env);
            return (NULL);
        }
        i++;
    }
    new_env[count] = ft_strdup(var);
    if (!new_env[count])
    {
        free_tab(new_env);
        return (NULL);
    }
    new_env[count + 1] = NULL;
    return (new_env);
}

int create_var(char *var, t_env *s_env)
{
    char    **new_env;
    char    **tmp;
    int    i;
    int     count;

    count = 0;
    i = 0;
    while (s_env->env && s_env->env[count])
        count++;
    new_env = core_create_var(var, s_env, count);
    if (!new_env)
        return (1);
    tmp = s_env->env;
    s_env->env = new_env;
    free_tab(tmp);
    return (0);
}

int export_options(t_cmd *cmd, t_env *s_env)
{
    t_index index;
    char    *var_to_create;

    index = (t_index){1, 0, 0};
    while (cmd->cmd[index.i])
    {
        index.j = 0;
        if (!ft_strchr(cmd->cmd[index.i], '='))
        {
            index.i++;
            continue;
        }
        if (parser_export(cmd->cmd[index.i]) == 1)
        {
            printf("minishell : %s: not a valid identifier\n", cmd->cmd[index.i]);
            index.i++;
            continue ;
        }
        index.k = is_var(cmd->cmd[index.i], s_env->env);
        if (index.k != -1 && concat_or_replace(index, cmd, s_env) == 1)
            return (1);
        else if (index.k == -1)
        {
            var_to_create = cmd->cmd[index.i];
            if (is_concatenate(cmd->cmd[index.i]))
                var_to_create = remove_concat_operator(cmd->cmd[index.i]);
            if (create_var(var_to_create, s_env) == 1)
            {
                if (is_concatenate(cmd->cmd[index.i]))
                    free(var_to_create);
                return (1);
            }
            if (is_concatenate(cmd->cmd[index.i]))
                free(var_to_create);
        }
        index.i++;
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