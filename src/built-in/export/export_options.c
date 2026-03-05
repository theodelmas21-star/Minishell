/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:51:52 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/05 08:31:42 by tdelmas2         ###   ########.fr       */
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

char *remove_concat_operator(char *cmd)
{
    char    *result;
    int     i;
    int     j;

    result = malloc(ft_strlen(cmd));
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (cmd[i])
    {
        if (cmd[i] == '+' && cmd[i + 1] == '=')
        {
            i++;
            continue;
        }
        result[j++] = cmd[i++];
    }
    result[j] = '\0';
    return (result);
}

int is_concatenate(char *cmd)
{
    t_index index;

    index.i = 0;
    while (cmd[index.i])
    {
        if (cmd[index.i] == '=')
        {
            if (cmd[index.i - 1] == '+')
                return (1);
            return (0);
        }
        index.i++;
    }
    return (0);
}

char *concatenate(char *cmd, char *env)
{
    t_index index;
    char    *tmp;
    int eq_pos;
    
    index = (t_index){0};
    eq_pos = 0;
    while (cmd[eq_pos] && cmd[eq_pos] != '=')
        eq_pos++;
    tmp = malloc(ft_strlen(env) + (ft_strlen(cmd) - eq_pos) + 1);
    if (!tmp)
        return (NULL);
    index.i = 0;
    index.k = 0;
    while (env[index.i])
        tmp[index.k++] = env[index.i++];
    index.i = eq_pos + 1;
    while (cmd[index.i])
        tmp[index.k++] = cmd[index.i++];
    tmp[index.k] = '\0';
    return (tmp);
}

int concat_or_replace(t_index index, t_cmd *cmd, t_env *s_env)
{
    char *tmp;
    char *con_str;

    if (is_concatenate(cmd->cmd[index.i]))
    {
        con_str = concatenate(cmd->cmd[index.i], s_env->env[index.k]);
        if (con_str == NULL)
            return (1);
        tmp = s_env->env[index.k];
        s_env->env[index.k] = con_str;
        free(tmp);
    }
    else
    {    
        tmp = s_env->env[index.k];
        s_env->env[index.k] = ft_strdup(cmd->cmd[index.i]);
        if (!s_env->env[index.k])
        {
            s_env->env[index.k] = tmp;
            return (1);
        }
        free(tmp);
    }
    return (0);
}
