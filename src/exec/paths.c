/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:00:01 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/31 11:25:50 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_path(t_env *envp)
{
	int	i;
	int	j;

	i = 0;
	envp->path = "PATH=";
	while (envp->env[i])
	{
		j = 0;
		while (envp->env[i][j] == envp->path[j])
		{
			j++;
			if (envp->path[j] == '\0')
			{
				envp->path = envp->env[i];
				break ;
			}
		}
		i++;
	}
	envp->path_split = ft_split(envp->path + 5, ':');
	if (!envp->path_split)
		return (NULL);
	return (envp);
}

int	is_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

char	*find_cmd_path(t_env *envp, t_cmd *cmd)
{
	char	*test_path;
	char	*temp_path;
	int		i;

	i = 0;
	if (cmd->cmd[0] == NULL)
		return (NULL);
	if (cmd->cmd[0][0] == '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (NULL);
	}
	if (is_directory(cmd->cmd[0]))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		return (NULL);
	}
	if (access(cmd->cmd[0], X_OK) == 0 || cmd->is_builtin == 1)
		return (cmd->cmd[0]);
	if (ft_strchr(cmd->cmd[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		if (access(cmd->cmd[0], F_OK) == 0)
		{
			ft_putstr_fd(": Permission denied\n", 2);
			cmd->cmd_error = 126;
		}
		else
			ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	if (!envp->path_split)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	while (envp->path_split[i])
	{
		temp_path = ft_strjoin(envp->path_split[i], "/");
		if (!temp_path)
			return (NULL);
		test_path = ft_strjoin(temp_path, cmd->cmd[0]);
		free(temp_path);
		if (!test_path)
			return (NULL);
		if (access(test_path, X_OK) == 0)
			return (test_path);
		free(test_path);
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (NULL);
}
