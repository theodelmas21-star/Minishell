/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:09:50 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/04 19:40:48 by tdelmas2         ###   ########.fr       */
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
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (0);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (0);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (0);
	if (ft_strncmp(cmd, "export", 8) == 0)
		return (0);
	if (ft_strncmp(cmd, "unset", 7) == 0)
		return (0);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (0);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (0);
	return (1);
}
