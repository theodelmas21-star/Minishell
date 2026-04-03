/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 11:16:10 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/04 00:24:53 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nbr_len(long n)
{
	int	len;

	len = (n <= 0);
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_putnbr(int n)
{
	long	nb;
	int		len;
	char	*res;

	nb = n;
	len = nbr_len(nb);
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

char	*interrogation(char *cmd, int exit_code)
{
	t_index	index;
	char	*new;
	char	*tmp;

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

void	adapt_data_null(int pos, t_cmd *cmd)
{
	t_index	index;

	index = (t_index){pos, pos, pos};
	while (cmd->sub_args[index.i] != -1)
	{
		cmd->sub_args[index.i] = cmd->sub_args[index.i + 1];
		cmd->quote_type[index.i] = cmd->quote_type[index.i + 1];
		cmd->is_expand[index.i] = cmd->is_expand[index.i + 1];
		index.i++;
	}
}

int	expander(t_list *cmds, t_env *s_env, int exit_code)
{
	t_cmd	*cur_cmd;
	t_list	*cur_list;
	int		size;

	cur_list = cmds;
	while (cur_list)
	{
		size = 0;
		cur_cmd = ((t_cmd *)cur_list->content);
		if (expand_cmd(cur_cmd, s_env, exit_code) == 1)
			return (1);
		cur_cmd->cmd = join_sub_args(cur_cmd);
		if (!cur_cmd->cmd)
			return (1);
		while (cur_cmd->cmd[size])
			size++;
		cur_cmd->sub_args[size] = -1;
		cur_list = cur_list->next;
	}
	return (0);
}
