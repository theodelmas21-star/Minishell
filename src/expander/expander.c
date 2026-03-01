/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:16:10 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/01 10:17:18 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int expand_cmd(t_cmd *cmd, t_env *s_env, int exit_code)
{
    t_index index;

    index = (t_index){0};
    (void)exit_code;
    while (cmd->cmd[index.i])
    {
        if (cmd->cmd[index.i][0] == '$' && cmd->is_expand[index.i] == 1)
        {
            if (call_exp_env(cmd, s_env, index.i) == 1)
                return (1);
        }
        index.i++;
    }
    return (0);
}

int expander(t_list *cmds, t_env *s_env, int exit_code)
{
    t_cmd *cur_cmd;
    t_list *cur_list;

    cur_list = cmds;
    while (cur_list)
    {
        cur_cmd = ((t_cmd *)cur_list->content);
        if (expand_cmd(cur_cmd, s_env, exit_code) == 1)
            return (1);
        cur_list = cur_list->next;
    }
    return (0);
}