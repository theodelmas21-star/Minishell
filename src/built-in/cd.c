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

static int update_env(t_env *s_env, char *target, char *new)
{
    t_index index;
    char    *tmp;
    int     len;

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

static char	*find_env_value(t_env *s_env, char *key)
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

int cd(t_cmd *cmd, t_env *s_env)
{
    char    *oldpwd;
    char    *newpwd;

    if (cmd->cmd[1] && cmd->cmd[2])
        return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
    if (!cmd->cmd[1])
    {
        if (!find_env_value(s_env, "HOME"))
                return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
        cmd->cmd[1] = find_env_value(s_env, "HOME");
    }
    if (ft_strncmp(cmd->cmd[1], "-", 2) == 0)
    {
        if (!find_env_value(s_env, "OLDPWD"))
            return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
        cmd->cmd[1] = find_env_value(s_env, "OLDPWD");
        ft_putstr_fd(cmd->cmd[1], 1);
        ft_putstr_fd("\n", 1);
    }
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd && find_env_value(s_env, "PWD"))
        oldpwd = ft_strdup(find_env_value(s_env, "PWD"));
    if (chdir(cmd->cmd[1]) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(cmd->cmd[1], 2);
        ft_putstr_fd(": ", 2);
        perror("");
        free(oldpwd);
        return (1);
    }
    newpwd = getcwd(NULL, 0);
    if (!newpwd)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(cmd->cmd[1], 2);
        ft_putstr_fd(": ", 2);
        perror("");
        free(oldpwd);
        return (1);
    }
    if (oldpwd && update_env(s_env, "OLDPWD=", oldpwd) == 1)
        return (free(oldpwd), free(newpwd), 1);
    if (update_env(s_env, "PWD=", newpwd) == 1)
        return (free(oldpwd), free(newpwd), 1);
    free(newpwd);
    free(oldpwd);
    return (0);
}
