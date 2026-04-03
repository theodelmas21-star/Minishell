/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:20:47 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 11:45:02 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*replace_old(char *old, char *new)
{
	char	*tmp;
	t_index	index;

	index = (t_index){0};
	while (old[index.j] && old[index.j] != '$')
		index.j++;
	tmp = malloc(sizeof(char) * (index.j + 1));
	if (!tmp)
		return (NULL);
	while (old[index.i] && old[index.i] != '$')
	{
		tmp[index.i] = old[index.i];
		index.i++;
	}
	tmp[index.i] = '\0';
	if (new)
	{
		tmp = ft_strjoin_free_both(tmp, new);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	return (tmp);
}

void	skip_dollar_var(char *old, int *dollar)
{
	int	count;

	count = 0;
	(*dollar)++;
	if (old[*dollar] == '{' || old[*dollar] == '[')
		count++;
	while (old[*dollar] && old[*dollar] != ' ' && old[*dollar] != '?'
		&& old[*dollar] != '*' && old[*dollar] != '%' && old[*dollar] != '@'
		&& old[*dollar] != '!' && old[*dollar] != '-' && old[*dollar] != '$'
		&& old[*dollar] != '.' && old[*dollar] != '}' && old[*dollar] != ']'
		&& old[*dollar] != '\'' && old[*dollar] != '=' && old[*dollar] != '/')
		(*dollar)++;
	if ((old[*dollar] == '}' || old[*dollar] == ']') && count == 1)
		(*dollar)++;
	if (old[*dollar] == '?')
		(*dollar)++;
}

char	*return_new_core(char *tmp, char *res, char *old, int *dollar)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		res[i] = tmp[i];
		i++;
	}
	skip_dollar_var(old, dollar);
	while (old[*dollar])
	{
		res[i] = old[*dollar];
		i++;
		(*dollar)++;
	}
	res[i] = '\0';
	return (res);
}

char	*return_new(char *old, char *new, int to_replace, int dollar)
{
	int		res_len;
	char	*res;
	char	*tmp;

	res_len = ft_strlen(old) + ft_strlen(new) - to_replace;
	res = malloc(sizeof(char) * (res_len + 1));
	if (!res)
		return (NULL);
	tmp = replace_old(old, new);
	if (!tmp)
		return (free(res), NULL);
	res = return_new_core(tmp, res, old, &dollar);
	if (!res)
		return (0);
	return (free(old), free(tmp), res);
}
