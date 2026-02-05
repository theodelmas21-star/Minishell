/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:00:01 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/05 11:43:33 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*find_path(t_env *envp)
{
	int	i;
	int j;

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
	return (envp);
}

char	*find_cmd_path(t_env *envp,t_cmd *cmd)
{
	char	*test_path;
	char	*temp_path;
	int		i;

	i = 0;
	if (access(cmd->cmd, X_OK) == 0)
		return (cmd->cmd);
	while (envp->path[i])
	{
		temp_path = ft_strjoin(envp->path[i], "/");
		if (!temp_path)
			return (NULL);
		test_path = ft_strjoin(temp_path, cmd->cmd[0]);
		free(temp_path);
		if (!test_path)
			return (NULL);
		if (access(test_path, X_OK) == 0)
			return (free(cmd->cmd[0]), test_path);
		free(test_path);
		i++;
	}
	ft_putstr_fd(cmd->cmd, 2);
	ft_putstr_fd(": Command not found", 2);
	ft_free_all(cmd->cmd);
	return (NULL);
}
