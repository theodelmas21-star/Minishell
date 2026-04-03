/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specific_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:31:43 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 13:34:11 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_number(char *new)
{
	char	*res;
	t_index	index;

	index = (t_index){0};
	while (new[index.i] && new[index.i] != ' ')
		index.i++;
	res = malloc(sizeof(char) * (index.i - 1));
	if (!res)
		return (NULL);
	while (new[index.j])
	{
		if (new[index.j] == '$' && new[index.j + 1] >= '0' && new[index.j
			+ 1] <= '9')
			index.j += 2;
		res[index.k] = new[index.j];
		index.j++;
		index.k++;
	}
	res[index.k] = '\0';
	return (free(new), res);
}
