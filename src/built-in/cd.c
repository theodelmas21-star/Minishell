/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 09:38:04 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/27 14:44:11 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int update_env(t_env *s_env, char *target, char *new)
{
    t_index index;
    char    *tmp;
    int     len;

    index = (t_index){0};
    len = ft_strlen(target);
    while (s_env->env[index.i])
    {
        if (ft_strncmp(s_env->env[index.i], target, len) == 0)
        {
            tmp = s_env->env[index.i];
            s_env->env[index.i] = ft_strjoin(target, new);
            if (!s_env->env[index.i])
                return (1);
            free(tmp);
        }
        index.i++;
    }
    return (0);
}

int cd(t_cmd *cmd, t_env *s_env)
{
    char *oldpwd;
    char *newpwd;
    
    if (!cmd->cmd[1] || cmd->cmd[2])
        return (write(2, "cd: invalid arguments\n", 22), 1);
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
        return (1);
    if (chdir(cmd->cmd[1]) == -1)
    {
        perror("cd");
        free(oldpwd);
        return (1);
    }
    newpwd = getcwd(NULL, 0);
    if (!newpwd)
        return (free(oldpwd), 1);
    if (update_env(s_env, "OLDPWD=", oldpwd) == 1)
        return (free(oldpwd), 1);
    if (update_env(s_env, "PWD=", newpwd) == 1)
        return (free(oldpwd), 1);
    free(newpwd);
    free(oldpwd);
    return (0);
}
