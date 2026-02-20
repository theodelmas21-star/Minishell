/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:59:39 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/20 10:51:00 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int size_env_built_in(char **env)
{
	int		i;
    int     index_char;
    int     size;
	
	i = 0;
    size = 0;
	if (!env)
		return (0);
	while (env[i])
	{
        index_char = 0;
        if (ft_strchr(env[i], '='))
        {
            while (env[i][index_char++])
                size++;
            size++;
        }
        i++;
	}
    size++;
	return (size);
}

int env(t_env *s_env)
{
	t_index index;
    char *tmp;

	index.i = 0;
	if (!s_env->env)
		return (1);
    tmp = malloc(sizeof(char) * size_env_built_in(s_env->env));
    if (!tmp)
    {
        return (1);
    }
	while (s_env->env[index.i])
	{
        index.j = 0;
        index.k = 0;
        if (ft_strchr(s_env->env[index.i], '='))
        {
            while (s_env->env[index.i][index.j])
                tmp[index.k++] = s_env->env[index.i][index.j++];
            tmp[index.k++] = '\n';
        }
		index.i++;
	}
    tmp[index.k] = '\0';
    printf("%s", tmp);
    return (free(tmp), 0);
}
