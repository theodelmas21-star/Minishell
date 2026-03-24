/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 08:13:58 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/24 09:43:06 by tdelmas2         ###   ########.fr       */
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
    while (str[ind_str] && str[ind_str] != ' ')
    {
        i++;
        ind_str++;
    }
    return (i);
}

int is_expandable(char *str)
{
	if (ft_strchr(str, '$'))
		return (1);
	return (0);
}

char **join_tab(char **cmd, char **tmp, char **new, int pos)
{
    t_index index;

    index = (t_index){0};
    while (index.i < pos)
    {
        new[index.i] = ft_strdup(cmd[index.i]);
        if (!new[index.i])
            return (NULL);
        index.i++;
    }
    while (tmp[index.j])
    {
        new[index.i] = ft_strdup(tmp[index.j]);
        if (!new[index.i])
            return (NULL);
        index.i++;
        index.j++;
    }
    index.k = pos + 1;
    while (cmd[index.k])
    {
        new[index.i] = ft_strdup(cmd[index.k]);
        if (!new[index.i])
            return (NULL);
        index.i++;
        index.k++;
    }
    new[index.i] = NULL;
    return (new);
}

char **join_split(char *str, char **cmd)
{
    char **tmp;
    t_index index;
    char **new;

    index = (t_index){0};
    if (ft_strchr(str, ' ') == NULL)
        return (cmd);
    tmp = ft_split(str, ' ');
    if (!tmp)
        return (NULL);
    while (cmd[index.i])
        index.i++;
    while(tmp[index.j])
        index.j++;
    while (cmd[index.k] != str)
        index.k++;
    new = malloc(sizeof(char *) * (index.i + index.j));
    if (!new)
        return (free_tab(tmp), NULL);
    new = join_tab(cmd, tmp, new, index.k);
    if (!new)
        return (free_tab(tmp), NULL);
    return (free_tab(tmp), free_tab(cmd), new);
}
