/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:09:50 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/04 14:23:40 by tdelmas2         ###   ########.fr       */
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
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (0);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return (0);
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (0);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (0);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (0);
	if (ft_strncmp(cmd, "env", 3) == 0)
		return (0);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		return (0);
	return (1);
}
