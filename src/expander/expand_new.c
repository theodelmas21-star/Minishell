/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:20:47 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/03 12:02:12 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_expand(t_cmd *cmd, int ind_cmd)
{
    t_index index;

    index = (t_index){0};
    while (cmd->cmd[ind_cmd][index.i])
    {
        if (cmd->cmd[ind_cmd][index.i] == '$')
            return (index.i);
        index.i++;
    }
    return (-1);
}

int len_new(char *str, int ind_str)
{
    int i;
    
    i = 0;
    if (str[i] >= '0' && str[i] <= '9')
        return (0);
    while (str[ind_str] && str[ind_str] != ' ')
    {
        i++;
        ind_str++;
    }
    return (i);
}

char *create_new(char *str, int ind_str)
{
    char *new;
    int len;
    t_index index;

    index = (t_index){0};
    len = len_new(str, ind_str);
    if (len == 0)
        return NULL;
    new = malloc(sizeof(char) * (len + 1));
    if (!new)
        return NULL;
    while (str[ind_str] && str[ind_str] != ' ')
    {
        new[index.i] = str[ind_str];
        index.i++;
        ind_str++;
    }
    new[index.i] = '\0';
    return (new);
}

char *replace_old(char *old, char *new)
{
    char *tmp;
    t_index index;

    index = (t_index){0};
    while (old[index.j] && old[index.j] != '$')
        index.j++;
    tmp = malloc(sizeof(char) * index.j + 1);
    if (!tmp)
        return (NULL);
    while (tmp[index.i] && tmp[index.i] != '$')
    {
        tmp[index.i] = old[index.i];
        index.i++;
    }
    tmp = ft_strjoin_free_both(tmp, new);
    if (!tmp)
        return (NULL);
    return (tmp);
}

char *return_new(char *old, char *new, int to_replace, int dollar)
{
    int res_len;
    char *res;
    char *tmp;
    t_index index;

    index = (t_index){0};
    res_len = ft_strlen(old) + ft_strlen(new) - to_replace;
    res = malloc(sizeof(char) * (res_len + 1));
    if (!res)
        return NULL;
    tmp = replace_old(old, new);
    if (!tmp)
        return (free(res), NULL);
    while (tmp[index.i])
    {
        res[index.i] = tmp[index.i];
        index.i++;
    }
    while(old[dollar] != ' ')
        dollar++;
    while(old[dollar])
    {
        res[index.i] = old[dollar];
        index.i++;
        dollar++;
    }
    res[index.i] = '\0';
    return (res);
}

char *expand_all(char *str, t_env *s_env, int exit_code)
{
    t_index index;
    char *new;
    int  to_replace;

    index = (t_index){0};
    while (str[index.i])
    {
        if (str[index.i] == '$')
        {
            index.i++;
            new = create_new(str, index.i);
            if (!new)
                return NULL;
            to_replace = ft_strlen(new);
            if (call_exp_env(new, s_env) == 1)
                return (1);
            if (interrogation(new, exit_code, index.i) == 1)
                return (1);
            new = return_new(str, new, to_replace, index.i);
            break;
        }
        index.i++;
    }
    return (new);
}
