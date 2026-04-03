/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:34:43 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/04 00:55:00 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_var(char *var, char **env)
{
	int	var_len;

	var_len = get_var_name_len(var);
	return (check_var_in_env(var, env, var_len));
}

char	**core_create_var(char *var, t_env *s_env, int count)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	while (i < count)
	{
		new_env[i] = ft_strdup(s_env->env[i]);
		if (!new_env[i])
		{
			free_tab(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = ft_strdup(var);
	if (!new_env[count])
	{
		free_tab(new_env);
		return (NULL);
	}
	new_env[count + 1] = NULL;
	return (new_env);
}

int	create_var(char *var, t_env *s_env)
{
	char	**new_env;
	char	**tmp;
	int		count;

	count = 0;
	while (s_env->env && s_env->env[count])
		count++;
	new_env = core_create_var(var, s_env, count);
	if (!new_env)
		return (1);
	tmp = s_env->env;
	s_env->env = new_env;
	free_tab(tmp);
	return (0);
}

int	export_options(t_cmd *cmd, t_env *s_env)
{
	int	i;
	int	error;

	i = 1;
	error = 0;
	while (cmd->cmd[i])
	{
		if (handle_export_arg(cmd, s_env, i) == 1)
			error = 1;
		i++;
	}
	return (error);
}

int	export(t_cmd *cmd, t_env *s_env)
{
	int	error_code;

	if (!cmd || !s_env)
		return (1);
	if (!cmd->cmd[1])
		return (simple_export(s_env));
	error_code = export_options(cmd, s_env);
	if (env_init(s_env, s_env->env) != 0)
		return (1);
	return (error_code);
}
