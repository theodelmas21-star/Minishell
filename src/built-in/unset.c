/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:56:14 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/22 20:54:39 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_valid(char *cmd, t_env *s_env)
{
    t_index index;

    index = (t_index){0};
    while (s_env->env[index.i])
    {
        if (ft_strncmp(cmd, s_env->env[index.i], ft_strlen(cmd)) == 0)
        {
            if (s_env->env[index.i][ft_strlen(cmd)] == '=')
                return (index.i);
        }
        index.i++;
    }
    return (-1);
}

char **replace(t_env *s_env, int target)
{
    char **new;
    t_index index;

    index = (t_index){0};
    while (s_env->env[index.j])
        index.j++;
    new = malloc(sizeof(char *) * index.j);
    if (!new)
        return NULL;
    while (s_env->env[index.i])
    {
        if (index.i != target)
        {
            new[index.k] = ft_strdup(s_env->env[index.i]);
            if (!new[index.k])
                return (free_tab(new), NULL);
            index.k++;
        }
        index.i++;
    }
    new[index.k] = NULL;
    free_tab(s_env->env);
    return (new);
}

int unset(t_cmd *cmd, t_env *s_env)
{
    t_index index;
    int     valid;
    int     ret;

    index = (t_index){1, 0, 0};
    ret = 0;
    while (cmd->cmd[index.i])
    {
        if (cmd->cmd[index.i][0] == '\0'
            || !ft_isalpha(cmd->cmd[index.i][0]))
        {
            ft_putstr_fd("minishell: unset: `", 2);
            ft_putstr_fd(cmd->cmd[index.i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
            ret = 1;
        }
        else
        {
            valid = is_valid(cmd->cmd[index.i], s_env);
            if (valid != -1)
            {
                s_env->env = replace(s_env, valid);
                if (!s_env->env)
                    return (1);
                if (ft_strncmp(cmd->cmd[index.i], "PATH",
                        ft_strlen(cmd->cmd[index.i])) == 0)
                {
                    free_tab(s_env->path_split);
                    s_env->path_split = NULL;
                }
            }
        }
        index.i++;
    }
    return (ret);
}
