/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:42:37 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/24 13:32:03 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_cmd *cmd)
{
	char *result;

	if (cmd->cmd[1] && ft_strncmp(&cmd->cmd[1][0], "-", 1) == 0)
	{
		printf("minishell: Only pwd without options is handled here.\n");
		return (1);
	}
	result = getcwd(NULL, 0);
	if (!result)
	{
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n",
			2);
		return (1);
	}
	else if (cmd->cmd[1])
		return (printf("%s\n", result), 0);
	printf("%s\n", result);
	free(result);
	return (0);
}