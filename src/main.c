/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:50:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/31 11:40:54 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_list *tokens)
{
	t_list	*current;
	t_token	*tok;
	t_list	*curr_sub;
	t_token	*subtok;

	current = tokens;
	while (current)
	{
		tok = (t_token *)current->content;
		printf("TOKEN:\n");
		printf("  arg = %s | type = %d | quote = %d\n", tok->arg, tok->type,
			tok->quote_type);
		curr_sub = tok->subtokens;
		while (curr_sub)
		{
			subtok = (t_token *)curr_sub->content;
			printf("    SUBTOKEN: arg = %s | type = %d | quote = %d\n",
				subtok->arg, subtok->type, subtok->quote_type);
			curr_sub = curr_sub->next;
		}
		printf("\n");
		current = current->next;
	}
}

void	print_cmds(t_list *cmds)
{
	t_list	*current;
	t_cmd	*cur_cmd;
	t_list	*cur_redir;
	t_redir	*redir;
	int		i;

	printf("CMDS:\n");
	while (cmds)
	{
		i = 0;
		current = cmds;
		cur_cmd = (t_cmd *)current->content;
		while (cur_cmd->cmd[i])
		{
			printf("%s\n", cur_cmd->cmd[i]);
			printf("is_expand[%d] = %d\n", i, cur_cmd->is_expand[i]);
			printf("subarg[%d] = %d\n", i, cur_cmd->sub_args[i]);
			printf("quote_type[%d] = %d\n", i, cur_cmd->quote_type[i]);
			printf("----\n");
			i++;
		}
		printf("isbuiltin = %d\n", cur_cmd->is_builtin);
		cur_redir = cur_cmd->redirs;
		while (cur_redir)
		{
			redir = (t_redir *)cur_redir->content;
			printf("redir target = %s \n", redir->target);
			printf("tok type = %u \n", redir->type);
			printf("delimiter = %s \n", redir->delimiter);
			printf("exp hd = %d \n", redir->exp_hd);
			printf("fd = %d \n", redir->fd);
			cur_redir = cur_redir->next;
		}
		printf("\n");
		cmds = cmds->next;
	}
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		printf("envp is NULL");
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*buffer;
	t_exec	exc;
	t_list	*tokens;
	t_list	*cmd;
	t_env	*s_env;
	t_index	index;

	(void)argc;
	(void)argv;
	(void)envp;
	exc.exit_code = 0;
	exc.error = 0;
	index = (t_index){0};
	exc.saved_stdin = dup(STDIN_FILENO);
	exc.saved_stdout = dup(STDOUT_FILENO);
	if (isatty(STDIN_FILENO))
	{
		init_signal();
		s_env = malloc(sizeof(t_env));
		if (!s_env)
			return (1);
		if (env_init(s_env, envp) == 1)
			return (free_s_env(s_env), 1);
		while (1)
		{
			dup2(exc.saved_stdin, STDIN_FILENO);
			dup2(exc.saved_stdout, STDOUT_FILENO);
			buffer = readline("minishell> ");
			if (!buffer)
				break ;
			if (g_signal)
			{
			 	exc.exit_code = g_signal;
			 	g_signal = 0;
			}
			tokens = lexer(buffer);
			//print_tokens(tokens);
			cmd = parsed_cmds(tokens, &exc.exit_code);
			//print_cmds(cmd);
			//printf("--------------------- Before Exec -------------------\n");
			free_list(tokens);
			exc.exit_code = call_exec(cmd, s_env, exc);
			free_cmds(cmd);
			if (*buffer)
				add_history(buffer);
			free(buffer);
		}
		free_s_env(s_env);
		close(exc.saved_stdin);
		close(exc.saved_stdout);
	}
	return (0);
}
