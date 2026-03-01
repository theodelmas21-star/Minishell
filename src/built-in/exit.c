/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:48:33 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/01 10:30:50 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void is_exit(t_list *cmds, t_env *s_env, int exit_code)
{
    t_cmd *cmd;

    cmd = ((t_cmd *)cmds->content);
    if (ft_strncmp(cmd->cmd[0], "exit", 4) != 0)
        return ;
    free_tab(cmd->cmd);
    if (cmd->redirs)
        free_list(cmd->redirs);
    free(cmd);
    free(cmds);
    if (s_env)
        free_s_env(s_env);
    printf("exit\n");
    exit(exit_code);
}
