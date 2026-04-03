/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:16:10 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 14:02:02 by tdelmas2         ###   ########.fr       */
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

int *adapt_is_exp(int pos, int len, t_cmd *cmd)
{
    int *new_is_expand;
    t_index index;
    
    index = (t_index){0};
    while (cmd->is_expand[index.i] != -1)
        index.i++;
    new_is_expand = malloc(sizeof(int) * (index.i + len));
    if (!new_is_expand)
        return NULL;
    while(index.j < pos)
    {
        new_is_expand[index.j] = cmd->is_expand[index.j];
        index.j++;
    }
    while (len > 0)
    {
        new_is_expand[index.j] = 0;
        index.j++;
        len--;
    }
    pos += 1;
    while (cmd->is_expand[pos] != -1)
    {
        new_is_expand[index.j] = cmd->is_expand[pos];
        index.j++;
        pos++;
    }
    new_is_expand[index.j] = cmd->is_expand[pos];
    return (free(cmd->is_expand), new_is_expand);
}

int *adapt_quote_type(int pos, int len, t_cmd *cmd)
{
    int *new;
    t_index index;
    
    index = (t_index){0};
    while (cmd->quote_type[index.i] != -1)
        index.i++;
    new = malloc(sizeof(int) * (index.i + len));
    if (!new)
        return NULL;
    while(index.j < pos)
    {
        new[index.j] = cmd->quote_type[index.j];
        index.j++;
    }
    while (len > 0)
    {
        new[index.j] = 1;
        index.j++;
        len--;
    }
    pos += 1;
    while (cmd->quote_type[pos] != -1)
    {
        new[index.j] = cmd->quote_type[pos];
        index.j++;
        pos++;
    }
    new[index.j] = cmd->quote_type[pos];
    return (free(cmd->quote_type), new);
}

int adapt_data(int pos, int len, t_cmd *cmd)
{
    cmd->is_expand = adapt_is_exp(pos, len, cmd);
    if (!cmd->is_expand)
        return (1);
    cmd->sub_args = adapt_sub_args(pos, len, cmd);
    if (!cmd->sub_args)
        return (1);
    cmd->quote_type = adapt_quote_type(pos, len, cmd);
    if (!cmd->quote_type)
        return (1);
    return (0);
}

void adapt_data_null(int pos, t_cmd *cmd)
{
    t_index index;

    index = (t_index){pos, pos, pos};
    while (cmd->sub_args[index.i] != -1)
    {
        cmd->sub_args[index.i] = cmd->sub_args[index.i + 1];
        cmd->quote_type[index.i] = cmd->quote_type[index.i + 1];
        cmd->is_expand[index.i] = cmd->is_expand[index.i + 1];
        index.i++;
    }
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
        cur_cmd->cmd = join_sub_args(cur_cmd);
        if (!cur_cmd->cmd)
            return (1);
        cur_list = cur_list->next;
    }
    return (0);
}
