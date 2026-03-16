/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 08:13:58 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/16 11:45:38 by tdelmas2         ###   ########.fr       */
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

char *join_split(char *str)
{
    char **tmp;
    int i;
    char *res;
    char *final;

    i = 0;
    if (ft_strchr(str, ' ') == NULL)
        return (str);
    tmp = ft_split(str, ' ');
    if (!tmp)
        return (NULL);
    res = tmp[i];
    i++;
    while (tmp[i])
    {
        res = ft_strjoin_free(res, " ", res);
        if (!res)
            return (NULL);
        res = ft_strjoin_free(res, tmp[i], res);
        if (!res)
            return (NULL);
        i++;
    }
    final = ft_strdup(res);
    if (!final)
        return (free_tab(tmp), NULL);
    return (free_tab(tmp), final);
}
