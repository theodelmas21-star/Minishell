/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:38:41 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/05 11:09:03 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error(char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}

int size_cmd(t_list *cmds)
{
    t_list *s_list;
	int		size;
	
	size = 0;
    s_list = cmds;
	if (!cmds)
		return (0);
	while (s_list)
	{
        size++;
		s_list = s_list->next;
	}
	return (size);
}

int init_env_local(t_env *s_env)
{
	t_env *env;

	env = malloc(sizeof(t_env));
    if (!env)
	{
        return (1);
	}
	env->env = NULL;
	s_env->path_split = NULL;
	s_env->path = NULL;
	s_env->local = ft_lstnew(env);
	if (!s_env->local)
		return (free(env), 1);
	return (0);
}

int	env_init(t_env *s_env, char **envp)
{
	char **copy;
	t_index	index;
	
	index = (t_index){0};
	while (envp[index.i])
		index.i++;
	copy = malloc(sizeof(char *) * (index.i + 1));
	if (!copy)
		return (1);
	while (envp[index.j])
	{
		copy[index.j] = ft_strdup(envp[index.j]);
		//copy[index.j + 1] = NULL;
		if (!copy[index.j])
			return (free_tab(copy), 1);
		index.j++;
	}
	copy[index.j] = NULL;
	s_env->env = copy;
    s_env = find_path(s_env);
	if (init_env_local(s_env) == 1)
		return (1);
	return (0);
}
