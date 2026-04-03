/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:09:50 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 10:10:06 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	verif_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		return (0);
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		return (0);
	if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		return (0);
	if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		return (0);
	if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		return (0);
	if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		return (0);
	if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		return (0);
	return (1);
}