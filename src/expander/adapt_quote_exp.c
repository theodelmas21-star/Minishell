/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adapt_quote_exp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:07:39 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 14:08:00 by tdelmas2         ###   ########.fr       */
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