/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 15:02:31 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/12 10:51:33 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int get_var_name_len(char *var)
{
    int i;

    i = 0;
    while (var[i] && var[i] != '=')
    {
        if (var[i] == '+' && var[i + 1] == '=')
            return (i);
        i++;
    }
    return (i);
}

int check_var_in_env(char *var, char **env, int var_len)
{
    int j;

    j = 0;
    while (env[j])
    {
        if (ft_strncmp(var, env[j], var_len) == 0 && env[j][var_len] == '=')
            return (j);
        j++;
    }
    return (-1);
}

int process_var_exists(t_cmd *cmd, t_env *s_env, int arg_idx, int var_idx)
{
    t_index index;

    index = (t_index){arg_idx, 0, var_idx};
    return (concat_or_replace(index, cmd, s_env));
}

int process_var_new(t_cmd *cmd, t_env *s_env, int arg_idx)
{
    char *var_to_create;
    int err;

    var_to_create = cmd->cmd[arg_idx];
    if (is_concatenate(cmd->cmd[arg_idx]))
    {
        var_to_create = remove_concat_operator(cmd->cmd[arg_idx]);
        if (!var_to_create)
            return (1);
    }
    err = create_var(var_to_create, s_env);
    if (is_concatenate(cmd->cmd[arg_idx]))
        free(var_to_create);
    return (err);
}

int handle_export_arg(t_cmd *cmd, t_env *s_env, int arg_idx)
{
    int var_len;
    int var_idx;

    if (!ft_strchr(cmd->cmd[arg_idx], '='))
        return (0);
    if (parser_export(cmd->cmd[arg_idx]) == 1)
    {
        printf("minishell : %s: not a valid identifier\n", cmd->cmd[arg_idx]);
        return (0);
    }
    var_len = get_var_name_len(cmd->cmd[arg_idx]);
    var_idx = check_var_in_env(cmd->cmd[arg_idx], s_env->env, var_len);
    if (var_idx != -1)
        return (process_var_exists(cmd, s_env, arg_idx, var_idx));
    return (process_var_new(cmd, s_env, arg_idx));
}
