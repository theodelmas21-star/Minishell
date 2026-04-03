/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:46:53 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 13:59:59 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fill_sub_args_len1(t_sub_args_helper *h, t_cmd *cmd)
{
	if (cmd->sub_args[h->pos] == cmd->sub_args[h->pos + 1])
		h->new[h->index->j] = cmd->sub_args[h->pos + 1];
	else
		h->new[h->index->j] = h->new[h->index->j - 1] + 1;
	h->index->j++;
}

void	fill_sub_args_middle(t_sub_args_helper *h, t_cmd *cmd)
{
	if (h->len == 1 && cmd->sub_args[h->pos] == cmd->sub_args[h->pos + 1])
	{
		h->new[h->index->j++] = cmd->sub_args[h->pos + 1] + 1;
		h->pos++;
		h->new[h->index->j++] = cmd->sub_args[h->pos] + 1;
		h->len--;
	}
	while (h->len > 1)
	{
		h->new[h->index->j] = h->new[h->index->j - 1] - 11000;
		h->index->j++;
		h->len--;
	}
	if (h->len == 1)
		fill_sub_args_len1(h, cmd);
}

int	*fill_sub_args_rest(t_sub_args_helper *h, t_cmd *cmd)
{
	h->pos += 1;
	while (cmd->sub_args[h->pos] != -1)
	{
		h->new[h->index->j] = cmd->sub_args[h->pos];
		h->index->j++;
		h->pos++;
	}
	h->new[h->index->j] = -1;
	return (free(cmd->sub_args), h->new);
}

int	*adapt_sub_args(int pos, int len, t_cmd *cmd)
{
	int					*new_sub_args;
	t_index				index;
	t_sub_args_helper	h;

	index = (t_index){0};
	while (cmd->sub_args[index.i] != -1)
		index.i++;
	new_sub_args = malloc(sizeof(int) * (index.i + len + 1));
	if (!new_sub_args)
		return (NULL);
	while (index.j < pos)
	{
		new_sub_args[index.j] = cmd->sub_args[index.j];
		index.j++;
	}
	new_sub_args[index.j] = cmd->sub_args[index.j];
	index.j++;
	len--;
	h = (t_sub_args_helper){new_sub_args, &index, len, pos};
	fill_sub_args_middle(&h, cmd);
	return (fill_sub_args_rest(&h, cmd));
}
