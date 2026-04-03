/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_quote_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:07:39 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 14:16:00 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fill_quote_type(t_sub_args_helper *h, t_cmd *cmd)
{
	while (h->index->j < h->pos)
	{
		h->new[h->index->j] = cmd->quote_type[h->index->j];
		h->index->j++;
	}
	while (h->len > 0)
	{
		h->new[h->index->j] = 1;
		h->index->j++;
		h->len--;
	}
	h->pos += 1;
	while (cmd->quote_type[h->pos] != -1)
	{
		h->new[h->index->j] = cmd->quote_type[h->pos];
		h->index->j++;
		h->pos++;
	}
	h->new[h->index->j] = cmd->quote_type[h->pos];
}

int	*adapt_quote_type(int pos, int len, t_cmd *cmd)
{
	int					*new;
	t_index				index;
	t_sub_args_helper	h;

	index = (t_index){0};
	while (cmd->quote_type[index.i] != -1)
		index.i++;
	new = malloc(sizeof(int) * (index.i + len));
	if (!new)
		return (NULL);
	h = (t_sub_args_helper){new, &index, len, pos};
	fill_quote_type(&h, cmd);
	return (free(cmd->quote_type), new);
}

static void	fill_is_exp(t_sub_args_helper *h, t_cmd *cmd)
{
	while (h->index->j < h->pos)
	{
		h->new[h->index->j] = cmd->is_expand[h->index->j];
		h->index->j++;
	}
	while (h->len > 0)
	{
		h->new[h->index->j] = 0;
		h->index->j++;
		h->len--;
	}
	h->pos += 1;
	while (cmd->is_expand[h->pos] != -1)
	{
		h->new[h->index->j] = cmd->is_expand[h->pos];
		h->index->j++;
		h->pos++;
	}
	h->new[h->index->j] = cmd->is_expand[h->pos];
}

int	*adapt_is_exp(int pos, int len, t_cmd *cmd)
{
	int					*new_is_expand;
	t_index				index;
	t_sub_args_helper	h;

	index = (t_index){0};
	while (cmd->is_expand[index.i] != -1)
		index.i++;
	new_is_expand = malloc(sizeof(int) * (index.i + len));
	if (!new_is_expand)
		return (NULL);
	h = (t_sub_args_helper){new_is_expand, &index, len, pos};
	fill_is_exp(&h, cmd);
	return (free(cmd->is_expand), new_is_expand);
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
