/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specific.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:34:50 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/16 11:27:06 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *handle_number(char *new)
{
    char *res;
    t_index index;

    index = (t_index){0};
    while (new[index.i] && new[index.i] != ' ')
        index.i++;
    res = malloc(sizeof(char) * (index.i - 1));
    if (!res)
        return (NULL);
    while (new[index.j])
    {
        if (new[index.j] == '$' && new[index.j + 1] >= '0' && new[index.j + 1] <= '9')
            index.j += 2;
        res[index.k] = new[index.j];
        index.j++;
        index.k++;
    }
    res[index.k] = '\0';
    return (free(new), res);
}

int size_sub_args(t_cmd *cmd)
{
    int size;
    t_index index;

    index = (t_index){0};
    size = 0;
    while (cmd->cmd[index.i])
        index.i++;
    while (index.k < index.i)
    {
        while (cmd->sub_args[index.j] == cmd->sub_args[index.k])
        {
            index.k++;
            index.j++;
        }
        size++;
        index.k++;
        index.j++;
    }
    return (size);
}

char **join_sub_args(t_cmd *cmd)
{
    t_index index;
    int size;
    char *new;
    char **res;

    index = (t_index){0, 0, 1};
    if (!cmd || !cmd->sub_args)
        return (cmd->cmd);
    size = size_sub_args(cmd);
    res = malloc(sizeof(char *) * (size + 1));
    if (!res)
        return (NULL);
    while (cmd->cmd[index.i])
    {
        new = ft_strdup(cmd->cmd[index.i]);
        if (!new)
            return (free(res), NULL);
        while (cmd->sub_args[index.i] == cmd->sub_args[index.j])
        {
            new = ft_strjoin(new, cmd->cmd[index.j]);
            if (!new)
                return (free(res), NULL);
            index.j++;
        }
        res[index.k] = ft_strdup(new);
            if (!res[index.k])
                return (free(res), NULL);
        free(new);
        index.i++;
    }
    free_tab(cmd->cmd);
    return (res);
}

int len_free_without_null(char **cmd, int i)
{
    t_index index;
    
    index = (t_index){0};
        while (cmd[index.i] && i == 0)
            index.i++;
        if (index.i == i && i == 0)
            index.i++;
        while (cmd[index.i] && i == 0)
            index.i++;
        while (cmd[index.i] && i == 1)
        {
            free(cmd[index.i]);
            index.i++;
        }
        if (index.i == i && i == 1)
            index.i++;
        while (cmd[index.i] && i == 1)
        {
            free(cmd[index.i]);
            index.i++;
        }
        if (i == 1)
            free(cmd);
        return (i);
}

char **without_null(char **cmd, int i)
{
    t_index index;
    char    **new;
    
    index = (t_index){0};
    index.i = len_free_without_null(cmd, 0);
    new = malloc(sizeof(char *) * index.i);
    if (!new)
        return NULL;
    while (cmd[index.j])
    {
        if (index.j == i)
            index.j++;
        new[index.k] = ft_strdup(cmd[index.j]);
        index.j++;
        index.k++;
        if (index.j == i)
            index.j++;
    }
    new[index.k] = NULL;
    index.i = len_free_without_null(cmd, 1);
    return (new);
}
