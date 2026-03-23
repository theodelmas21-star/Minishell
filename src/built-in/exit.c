/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:48:33 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/23 22:26:08 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	is_exit(t_list *cmds, t_env *s_env, int exit_code)
{
	t_cmd	*cmd;

	cmd = ((t_cmd *)cmds->content);
	if (ft_strncmp(cmd->cmd[0], "exit", 5) != 0)
		return ;
	printf("exit\n");
	if (cmd->cmd[1] && !is_numeric(cmd->cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 2;
	}
	else if (cmd->cmd[1] && cmd->cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        exit_code = 1;
	}
	else if (cmd->cmd[1])
		exit_code = (unsigned char)ft_atoi(cmd->cmd[1]);
	free_cmds(cmds);
	if (s_env)
		free_s_env(s_env);
	exit(exit_code);
}
