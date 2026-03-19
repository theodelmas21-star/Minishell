/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 10:00:01 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/19 10:48:12 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_path(t_env *envp)
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
	envp->path_split = ft_split(envp->path + 5, ':');
	if (!envp->path_split)
		return (NULL);
	return (envp);
}

char	*find_cmd_path(t_env *envp,t_cmd *cmd)
{
	char	*test_path;
	char	*temp_path;
	int		i;

	i = 0;
	if (cmd->cmd[0] == NULL)
	{
		printf("minishell: %s: command not found\n", cmd->cmd[0]);
		return NULL;
	}
	if (access(cmd->cmd[0], X_OK) == 0 || cmd->is_builtin == 1)
		return (cmd->cmd[0]);
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
			return (free(cmd->cmd[0]), test_path);
		free(test_path);
		i++;
	}
	printf("minishell: %s: command not found\n", cmd->cmd[0]);
	return (NULL);
}
