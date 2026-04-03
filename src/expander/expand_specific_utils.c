/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specific_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 13:31:43 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 14:37:27 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_dollar_digit(char *str, int i)
{
	if (str[i] == '$' && str[i + 1] >= '0' && str[i + 1] <= '9')
		return (0);
	return (1);
}

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
		if (is_dollar_digit(new, index.j))
			index.j += 2;
		res[index.k] = new[index.j];
		index.j++;
		index.k++;
	}
	res[index.k] = '\0';
	return (free(new), res);
}
