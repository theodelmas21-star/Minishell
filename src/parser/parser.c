/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 13:22:27 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/05 15:13:29 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd *create_cmd(t_token *token)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd *));
    if (!cmd)
        return (NULL);
    cmd->cmd = "";
    while (token->type == WORD)
    {
        cmd->cmd = token->arg
    }
}

t_list *token_to_cmd(t_list *tokens)
{
    t_index index;
    t_cmd   *cmd;
    t_list  *list_cmds;
    t_token tmp;

    if (!tokens)
        return (NULL);
    create_cmd(tokens->content);
}
