/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 14:48:33 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/26 14:40:37 by ssivilay         ###   ########.fr       */
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

static int	is_overflow(char *str)
{
	int	len;
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	len = ft_strlen(str + i);
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (str[0] == '-')
		return (ft_strncmp(str + i, "9223372036854775808", 19) > 0);
	return (ft_strncmp(str + i, "9223372036854775807", 19) > 0);
}

static int	long_long_atoi(char *str)
{
	int			i;
	int			sign;
	long long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((unsigned char)(res * sign));
}

int	is_exit(t_cmd *cmd, t_list *cmds, t_env *s_env, int exit_code, int in_pipe)
{
	if (ft_strncmp(cmd->cmd[0], "exit", 5) != 0)
		return (0);
	if (!in_pipe)
		printf("exit\n");
	if (cmd->cmd[1] && (!is_numeric(cmd->cmd[1])
			|| is_overflow(cmd->cmd[1])))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 2;
	}
	else if (cmd->cmd[1] && cmd->cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		if (in_pipe)
			exit(1);
		return (1);
	}
	else if (cmd->cmd[1])
		exit_code = long_long_atoi(cmd->cmd[1]);
	if (!in_pipe)
	{
		free_cmds(cmds);
		if (s_env)
			free_s_env(s_env);
	}
	exit(exit_code);
}
