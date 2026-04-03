/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 09:32:32 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 11:03:15 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_newline(char *res)
{
	t_index	index;
	char	*new;

	index = (t_index){0};
	new = malloc(sizeof(char) * (ft_strlen(res) + 2));
	if (!new)
		return (free(res), NULL);
	while (res[index.i])
	{
		new[index.i] = res[index.i];
		index.i++;
	}
	new[index.i++] = '\n';
	new[index.i] = '\0';
	return (free(res), new);
}

char	*error_case_expand_hd(t_cmd *tmp, t_exec *exc)
{
	exc->error = 1;
	return (free_cmd(tmp), NULL);
}

char	*expand_hd(char *res, t_env *s_env, t_exec *exc, int is_newline)
{
	t_cmd	*tmp;
	char	*final;

	if (!res)
		return (NULL);
	if (ft_strchr(res, '$') == NULL)
		return (res);
	tmp = init_tmp(res);
	if (!tmp)
		return (NULL);
	if (expand_cmd(tmp, s_env, exc->exit_code) == 1)
		return (error_case_expand_hd(tmp, exc));
	if (!tmp->cmd[0])
		return (error_case_expand_hd(tmp, exc));
	if (is_newline)
		tmp->cmd[0] = add_newline(tmp->cmd[0]);
	if (!tmp->cmd[0])
		return (error_case_expand_hd(tmp, exc));
	final = ft_strdup(tmp->cmd[0]);
	if (!final)
		return (error_case_expand_hd(tmp, exc));
	free_cmd(tmp);
	return (final);
}
