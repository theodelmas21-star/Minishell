/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:34:52 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/27 13:45:25 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int handle_builtins_second(t_cmd *cmd, t_env *s_env, int i, int pid)
{
    if (ft_strncmp(cmd->cmd[0], "export", i) == 0)
    {
        if (pid == 0)
            exit(export(cmd, s_env));
        return (export(cmd, s_env));
    }
    else if (ft_strncmp(cmd->cmd[0], "pwd", i) == 0)
    {
        if (pid == 0)
            exit(pwd(cmd));
        return (pwd(cmd));
    }
    else if (ft_strncmp(cmd->cmd[0], "unset", i) == 0)
    {
        if (pid == 0)
            exit(unset(cmd, s_env));
        return (unset(cmd, s_env));
    }
    return (0);
}

int handle_builtins(t_cmd *cmd, t_env *s_env, int pid)
{
    int i;

    i = ft_strlen(cmd->cmd[0]);
    if (ft_strncmp(cmd->cmd[0], "echo", i) == 0)
    {
        if (pid == 0)
            exit(echo(cmd));
        return (echo(cmd));
    }
    else if (ft_strncmp(cmd->cmd[0], "env", i) == 0)
    {
        if (cmd->cmd[1])
        {
            printf("Only env without options or args is handled here.");
            exit(1);
        }
        if (pid == 0)
            exit(env(s_env));
        return (env(s_env));
    }
    handle_builtins_second(cmd, s_env, i, pid);
    return (0);
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
