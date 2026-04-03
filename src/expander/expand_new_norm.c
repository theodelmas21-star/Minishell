/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new_norm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 11:44:20 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 11:46:43 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_var_char(char c)
{
	if (!c || c == ' ' || c == '%' || c == '=' || c == '@')
		return (0);
	if (c == '*' || c == '!' || c == '.' || c == '-')
		return (0);
	if (c == '}' || c == ']' || c == '\'' || c == '/')
		return (0);
	return (1);
}

char	*create_new(char *str, int ind_str)
{
	char	*new;
	int		len;
	t_index	index;

	index = (t_index){0};
	len = len_new(str, ind_str);
	if (len == 0)
		return (NULL);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (is_valid_var_char(str[ind_str]))
	{
		if (str[ind_str] == '{')
			ind_str++;
		new[index.i] = str[ind_str];
		index.i++;
		ind_str++;
		if (str[ind_str] == '$' || str[ind_str - 1] == '?')
			break ;
	}
	new[index.i] = '\0';
	return (new);
}