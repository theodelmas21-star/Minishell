
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:38:04 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/23 12:50:20 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_env(t_env *s_env, char *target, char *new)
{
	t_index	index;
	char	*tmp;
	int		len;

	index = (t_index){0};
	len = ft_strlen(target);
	while (s_env->env[index.i])
	{
		if (ft_strncmp(s_env->env[index.i], target, len) == 0)
		{
			tmp = s_env->env[index.i];
			s_env->env[index.i] = ft_strjoin(target, new);
			if (!s_env->env[index.i])
				return (1);
			free(tmp);
		}
		index.i++;
	}
	return (0);
}

char	*find_env_value(t_env *s_env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (s_env->env[i])
	{
		if (ft_strncmp(s_env->env[i], key, len) == 0
			&& s_env->env[i][len] == '=')
			return (s_env->env[i] + len + 1);
		i++;
	}
	return (NULL);
}
