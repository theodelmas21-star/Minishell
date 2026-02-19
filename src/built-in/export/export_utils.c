/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:42:48 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/19 11:54:10 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	size_env_export(char **env)
{
	int	i;
	int	index_char;
	int	size;

	i = 0;
	size = 0;
	if (!env)
		return (1);
	while (env[i])
	{
		index_char = 0;
		if (ft_strchr(env[i], '='))
		{
			while (env[i][index_char++])
				size++;
		}
		i++;
	}
	size++;
	return (size);
}

char	*mid_core(t_env *s_env, t_index index)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * ft_strlen(s_env->env[index.i]) + 2);
	if (!tmp)
		return (NULL);
	while (s_env->env[index.i][index.j] != '=')
		tmp[index.j] = s_env->env[index.i][index.j++];
	tmp[index.j] = s_env->env[index.i][index.j++];
	tmp[index.j++] = '\"';
	while (s_env->env[index.i][index.j])
		tmp[index.j] = s_env->env[index.i][index.j++];
	tmp[index.j++] = '\"';
	tmp[index.j] = '\0';
	return (tmp);
}

char	**make_it_dquote(t_env *s_env)
{
	t_index	index;
	char	*tmp;
	char	**env_exp;

	index.i = 0;
	index.k = 0;
	env_exp = malloc(sizeof(char *) * size_env_export(s_env->env));
	if (!env_exp)
		return (1);
	while (s_env->env[index.i])
	{
		index.j = 0;
		if (ft_strchr(s_env->env, '='))
		{
			env_exp[index.k] = mid_core(s_env, index);
			if (!env_exp[index.k])
				return (free_tab(env_exp), NULL);
			index.k++;
		}
		index.i++;
	}
	env_exp[index.k] = NULL;
	return (env_exp);
}

int	simple_export(t_cmd *cmd, t_env *s_env)
{
	char **env_exp;
	t_index index;

	env_exp = make_it_dquote(s_env);
	if (!env_exp)
		return (1);
	index.i = 0;
	while (env_exp[index.i])
	{
		index.j = index.i - 1;
		env_exp[index.i] = ft_strjoin_free("export ", env_exp[index.i],
				env_exp[index.i]);
		if (!env_exp[index.i])
			return (free_tab(env_exp), 1);
		env_exp[index.i] = ft_strjoin_free(env_exp[index.i], "\n",
				env_exp[index.i]);
		if (!env_exp[index.i])
			return (free_tab(env_exp), 1);
		if (index.j >= 0)
		{
			env_exp[index.i] = ft_strjoin_free_both(env_exp[index.j],
					env_exp[index.i]);
			if (!env_exp[index.i])
				return (free_tab(env_exp), 1);
		}
		index.i++;
	}
	return (printf(env_exp[index.i - 1]), free_tab(env_exp), 0);
}