/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:51:52 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/06 10:38:09 by tdelmas2         ###   ########.fr       */
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
    char *eq_cmd;
    char *eq_env;
    char *tmp;
    int len;

    eq_cmd = ft_strchr(cmd, '=');
    eq_env = ft_strchr(env, '=');
    if (!eq_cmd || !eq_env)
        return (NULL);
    len = (eq_env - env + 1) + ft_strlen(eq_env + 1) + ft_strlen(eq_cmd + 1);
    tmp = malloc(len + 1);
    if (!tmp)
        return (NULL);
    ft_strlcpy(tmp, env, eq_env - env + 2);
    ft_strlcat(tmp, eq_env + 1, len + 1);
    ft_strlcat(tmp, eq_cmd + 1, len + 1);
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
