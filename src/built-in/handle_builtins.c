/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:34:52 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/22 20:54:34 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int handle_builtins_second(t_cmd *cmd, t_env *s_env, int pid)
{
    if (ft_strncmp(cmd->cmd[0], "export", 8) == 0)
    {
        if (pid == 0)
            exit(export(cmd, s_env));
        return (export(cmd, s_env));
    }
    else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
    {
        if (pid == 0)
            exit(pwd(cmd));
        return (pwd(cmd));
    }
    else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
    {
        if (pid == 0)
            exit(unset(cmd, s_env));
        return (unset(cmd, s_env));
    }
    else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
    {
        if (pid == 0)
            exit(cd(cmd, s_env));
        return (cd(cmd, s_env));
    }
    return (0);
}

int handle_builtins(t_cmd *cmd, t_env *s_env, int pid)
{
    if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
    {
        if (pid == 0)
            exit(echo(cmd));
        return (echo(cmd));
    }
    else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
    {
        if (cmd->cmd[1])
        {
            printf("Only env without options or args is handled here.\n");
            if (pid == 0)
                exit(1);
            return (1);
        }
        if (pid == 0)
            exit(env(s_env));
        return (env(s_env));
    }
    else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0 && pid == 0)
        exit(0);
    return (handle_builtins_second(cmd, s_env, pid));
}

/*Builtin	            Seul	                            Dans un pipe

cd	                    parent	                            enfant
export	                parent	                            enfant
unset	                parent	                            enfant
exit	                parent	                            enfant
echo	                enfant ou parent	                enfant
pwd	                    enfant ou parent	                enfant

1. echo
2. pwd
3. env
4. export
5. unset
6. cd
7. exit
*/
