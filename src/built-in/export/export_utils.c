/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 09:42:48 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/27 09:51:38 by tdelmas2         ###   ########.fr       */
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

char	*mid_core(char *env)
{
	char	*tmp;
	t_index index;

	index = (t_index){0};
	tmp = malloc(sizeof(char) * (ft_strlen(env) + 3));
	if (!tmp)
		return (NULL);
	while (env[index.j])
	{
		tmp[index.k] = env[index.j];
		index.j++;
		index.k++;
		if (tmp[index.k - 1] == '=' && index.i == 0)
		{
			tmp[index.k] = '\"';
			index.k++;
			index.i++;
		}
	}
	tmp[index.k++] = '\"';
	tmp[index.k] = '\0';
	return (tmp);
}

char	**make_it_dquote(t_env *s_env)
{
	t_index	index;
	char	**env_exp;

	index.i = 0;
	index.k = 0;
	env_exp = malloc(sizeof(char *) * size_env_export(s_env->env));
	if (!env_exp)
		return (NULL);
	while (s_env->env[index.i])
	{
		if (ft_strchr(s_env->env[index.i], '=') != NULL)
		{
			env_exp[index.k] = mid_core(s_env->env[index.i]);
			if (!env_exp[index.k])
				return (free_tab(env_exp), NULL);
			index.k++;
		}
		index.i++;
	}
	env_exp[index.k] = NULL;
	return (env_exp);
}

int simple_export_loop(char **env_exp)
{
	t_index index;

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
	return (0);
}

int	simple_export(t_env *s_env)
{
	char **env_exp;
	t_index index;

	env_exp = make_it_dquote(s_env);
	if (!env_exp)
		return (1);
	index.i = 0;
	if (simple_export_loop(env_exp) == 1)
		return (1);
	while (env_exp[index.i])
		index.i++;
	printf("%s", env_exp[index.i - 1]);
	free (env_exp[index.i - 1]);
	free (env_exp);
	return (0);
}
