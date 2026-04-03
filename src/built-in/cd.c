/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:52:55 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 14:54:12 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_cd_target(t_cmd *cmd, t_env *s_env)
{
	char	*target;

	target = cmd->cmd[1];
	if (target && cmd->cmd[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), NULL);
	if (!target)
	{
		target = find_env_value(s_env, "HOME");
		if (!target)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
	}
	if (ft_strncmp(target, "-", 2) == 0)
	{
		target = find_env_value(s_env, "OLDPWD");
		if (!target)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), NULL);
		ft_putstr_fd(target, 1);
		ft_putstr_fd("\n", 1);
	}
	return (target);
}

int	cd_error(char *target, char *oldpwd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	free(oldpwd);
	return (1);
}

int	update_pwd(t_env *s_env, char *oldpwd, char *newpwd)
{
	if (oldpwd && update_env(s_env, "OLDPWD=", oldpwd) == 1)
		return (free(oldpwd), free(newpwd), 1);
	if (update_env(s_env, "PWD=", newpwd) == 1)
		return (free(oldpwd), free(newpwd), 1);
	free(newpwd);
	free(oldpwd);
	return (0);
}

int	cd(t_cmd *cmd, t_env *s_env)
{
	char	*oldpwd;
	char	*newpwd;
	char	*target;

	target = get_cd_target(cmd, s_env);
	if (!target)
		return (1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd && find_env_value(s_env, "PWD"))
		oldpwd = ft_strdup(find_env_value(s_env, "PWD"));
	if (chdir(target) == -1)
		return (cd_error(target, oldpwd));
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (cd_error(target, oldpwd));
	return (update_pwd(s_env, oldpwd, newpwd));
}
