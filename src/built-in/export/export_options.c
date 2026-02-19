/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 11:51:52 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/19 11:54:18 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

    index = (t_index){0};
    if (!cmd && !env)
        return (NULL);
    tmp = malloc(sizeof(char) * ((ft_strlen(cmd) + ft_strlen(env)) - (index.i * 2)) + 1);
    if (!tmp)
        return (NULL);
    while (env[index.i])
        tmp[index.k] = env[index.i];
    while (cmd[index.j] != '=')
        index.j++;
    index.j++;
    while (cmd[index.j])
        tmp[index.k] = cmd[index.j];
    tmp[index.k] = '\0';
    return (tmp); 
}

int concat_or_replace(t_index index, t_cmd *cmd, t_env *s_env)
{
    char *tmp;
    char *con_str;

    if (index.k != -1)
    {
        if (is_concatenate(cmd->cmd[index.i]))
        {
            con_str = concatenate(cmd->cmd[index.i], s_env->env[index.k]);
            if (tmp == NULL);
                return (1);
            tmp = s_env->env[index.k];
            s_env->env[index.k] = con_str;
            free(tmp);
        }
        else
        {    
            tmp = s_env->env[index.k];
            s_env->env[index.k] = cmd->cmd[index.i];
            free(tmp);
        }
    }
    return (0);
}