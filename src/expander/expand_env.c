/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 09:50:06 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/03 10:36:16 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_env(char *cmd, t_env *s_env)
{
    t_index index;

    index = (t_index){0};
    while (s_env->env[index.i])
    {
        if (!ft_strncmp(cmd + 1, s_env->env[index.i], ft_strlen(cmd) - 1)
            && s_env->env[index.i][ft_strlen(cmd) - 1] == '=')
            return (index.i);
        index.i++;
    }
    return (-1);
}

int len_new(char *env)
{
    int start_len;
    int len;
    t_index index;
    
    index = (t_index){0};
    len = 0;
    start_len = 0;
    while (env[index.j])
    {
        if (env[index.j] == '=' && start_len == 0)
        {
            index.j++;
            start_len = 1;
        }
        if (start_len == 1)
            len++;
        index.j++;
    }
    return (len);
}

char *expand_env(t_env *s_env, int ind_env)
{
    t_index index;
    char *new;
    int start;

    start = 0;
    index = (t_index){0};
    index.i = ind_env;
    new = malloc(sizeof(char) * (len_new(s_env->env[index.i] + 1)));
    if (!new)
        return NULL;
    while (s_env->env[index.i][index.j])
    {
        if (s_env->env[index.i][index.j] == '=' && start == 0)
        {
            index.j++;
            start = 1;
        }
        if (start == 1)
            new[index.k++] = s_env->env[index.i][index.j];
        index.j++;
    }
    new[index.k] = '\0';
    return (new);
}

int call_exp_env(char *cmd, t_env *s_env)
{
    char *tmp2;
    int  ind_env;
    
    ind_env = is_env(cmd, s_env);
    if (ind_env >= 0)
    {
        tmp2 = cmd;
        cmd = expand_env(s_env, ind_env);
        if (!cmd)
            return (1);
        free(tmp2);
    }
    return (0);
}
