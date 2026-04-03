/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:50:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/03 15:17:01 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_s_env(char **envp)
{
	t_env	*s_env;

	s_env = malloc(sizeof(t_env));
	if (!s_env)
		return (NULL);
	s_env->env = NULL;
	s_env->path = NULL;
	s_env->path_split = NULL;
	if (env_init(s_env, envp) == 1)
		return (free_s_env(s_env), NULL);
	return (s_env);
}

void	main_loop(t_env *s_env, t_exec *exc)
{
	char	*buffer;
	t_list	*tokens;
	t_list	*cmd;

	while (1)
	{
		dup2(exc->saved_stdin, STDIN_FILENO);
		dup2(exc->saved_stdout, STDOUT_FILENO);
		buffer = readline("minishell> ");
		if (!buffer)
			break ;
		if (g_signal)
		{
			exc->exit_code = g_signal;
			g_signal = 0;
		}
		tokens = lexer(buffer);
		cmd = parsed_cmds(tokens, &exc->exit_code);
		free_list(tokens);
		exc->exit_code = call_exec(cmd, s_env, *exc);
		free_cmds(cmd);
		if (*buffer)
			add_history(buffer);
		free(buffer);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_exec	exc;
	t_env	*s_env;

	(void)argc;
	(void)argv;
	exc.exit_code = 0;
	exc.error = 0;
	exc.saved_stdin = dup(STDIN_FILENO);
	exc.saved_stdout = dup(STDOUT_FILENO);
	if (isatty(STDIN_FILENO))
	{
		init_signal();
		s_env = init_s_env(envp);
		if (!s_env)
			return (1);
		main_loop(s_env, &exc);
		free_s_env(s_env);
		close(exc.saved_stdin);
		close(exc.saved_stdout);
	}
	return (0);
}
