/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:16:10 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/15 09:29:37 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nbr_len(long n)
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

char *interrogation(char *cmd, int exit_code)
{
    t_index index;
    char    *new;
    char    *tmp;

    index = (t_index){1, 0, 0};
    if (cmd[index.i] == '?')
    {
        new = ft_putnbr(exit_code);
        if (!new)
            return (NULL);
        tmp = cmd;
        cmd = ft_strjoin_free(new, cmd + 2, new);
        if (!cmd)
            return (NULL);
        free(tmp);
    }
    return (cmd);
}

int expand_cmd(t_cmd *cmd, t_env *s_env, int exit_code)
{
    t_index index;

    index = (t_index){0};
    (void)exit_code;
    while (cmd->cmd[index.i])
    {
        if (is_expandable(cmd->cmd[index.i]) && cmd->is_expand[index.i] > 0)
        {
            cmd->cmd[index.i] = expand_all(cmd->cmd[index.i], s_env, exit_code);
            if (!cmd->cmd[index.i])
                return (1);
        }
        if (cmd->is_expand[index.i] == 1)
        {
            cmd->cmd[index.i] = join_split(cmd->cmd[index.i]);
            if (!cmd->cmd[index.i])
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