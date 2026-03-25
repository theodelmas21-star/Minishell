/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 09:20:47 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/25 11:48:11 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (str[ind_str] && str[ind_str] != ' ' && str[ind_str] != '%' && str[ind_str] != '='
		&& str[ind_str] != '@' && str[ind_str] != '*' && str[ind_str] != '!' && str[ind_str] != '.'
		&& str[ind_str] != '-' && str[ind_str] != '}' && str[ind_str] != ']' && str[ind_str] != '\'')
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

char	*return_new_core(char *tmp, char *res, char *old, int *dollar)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tmp[i])
	{
		res[i] = tmp[i];
		i++;
	}
	(*dollar)++;
	if (old[*dollar] == '{' || old[*dollar] == '[')
		count++;
	while (old[*dollar] && old[*dollar] != ' ' && old[*dollar] != ' ' && old[*dollar] != '?'
		&& old[*dollar] != '*' && old[*dollar] != '%' && old[*dollar] != '@'
		&& old[*dollar] != '!' && old[*dollar] != '-' && old[*dollar] != '$' && old[*dollar] != '.'
		&& old[*dollar] != '}' && old[*dollar] != ']' && old[*dollar] != '\'' && old[*dollar] != '=')
		(*dollar)++;
	if ((old[*dollar] == '}' || old[*dollar] == ']') && count == 1)
		(*dollar)++;
	if (old[*dollar] == '?')
		(*dollar)++;
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

char	*expand_all(t_cmd *cmd, t_env *s_env, int exit_code, int str)
{
	t_index	index;
	char	*new;
	int		to_replace;

	index = (t_index){0};
	while (cmd->cmd[str][index.i])
	{
		if (cmd->cmd[str][index.i] == '$' && cmd->cmd[str][index.i + 1] && cmd->cmd[str][index.i + 1] != ' ' && cmd->cmd[str][index.i + 1] != '='
			&& cmd->cmd[str][index.i + 1] != ':' && cmd->cmd[str][index.i + 1] != '%' && cmd->cmd[str][index.i + 1] != '\'')
		{
			new = create_new(cmd->cmd[str], index.i);
			if (!new)
				return (NULL);
			to_replace = ft_strlen(new);
			if (new[1] == '?' && new[2] == '\0')
			{
				new = interrogation(new, exit_code);
				if (!new)
					return (NULL);
			}
			else if (is_env(new, s_env) >= 0)
			{
				new = call_exp_env(new, s_env);
				if (!new)
					return (NULL);
			}
			else if (new[1] >= '0' && new[1] <= '9')
			{
				new = handle_number(new);
				if (!new)
					return (NULL);
			}
			else
			{
				new = ft_strdup("");
				index.k = 1;
			}
			index.j = ft_strlen(new);
			new = return_new(cmd->cmd[str], new, to_replace, index.i);
			if (!new)
				return (NULL);
			cmd->cmd[str] = new;
			index.i += index.j - 1;
		}
		else if (cmd->cmd[str][index.i] == '$' && !cmd->cmd[str][index.i + 1] && cmd->quote_type[str + 1] == 2)
		{
			new = ft_strdup("");
			index.k = 1;
			index.j = ft_strlen(new);
			new = return_new(cmd->cmd[str], new, to_replace, index.i);
			if (!new)
				return (NULL);
			cmd->cmd[str] = new;
			index.i += index.j - 1;
		}
		index.i++;
	}
	if (index.k == 1 && cmd->cmd[str][0] == '\0' && cmd->quote_type[index.i] != 2)
		return (free(cmd->cmd[str]), NULL);
	return (cmd->cmd[str]);
}
