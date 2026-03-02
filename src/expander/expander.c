/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:16:10 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/02 09:15:04 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <stdlib.h>

static int	nbr_len(long n)
{
	int len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_putnbr(int n)
{
	long	nb = n;
	int		len = nbr_len(nb);
	char	*res;

	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (nb < 0)
		nb = -nb;
	if (n == 0)
		res[0] = '0';
	while (nb)
	{
		res[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}

int interrogation(t_cmd *cmd, int exit_code, int cmd_ind)
{
    t_index index;
    char    *new;
    char    *tmp;

    index = (t_index){1, 0, 0};
    if (cmd->cmd[cmd_ind][index.i] == '?')
    {
        new = ft_putnbr(exit_code);
        if (!new)
            return (1);
        tmp = cmd->cmd[cmd_ind];
        cmd->cmd[cmd_ind] = ft_strjoin_free(new, cmd->cmd[cmd_ind] + 2, new);
        if (!cmd)
            return (1);
        free(tmp);
    }
    return (0);
}

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
            if (interrogation(cmd, exit_code, index.i) == 1)
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