/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 14:38:41 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/01 11:27:26 by tdelmas2         ###   ########.fr       */
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
	free_tab(s_env->env);
	free_tab(s_env->path_split);
	s_env->env = copy;
    s_env = find_path(s_env);
	return (0);
}
