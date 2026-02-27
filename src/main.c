/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:50:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/03/09 14:34:47 by tdelmas2         ###   ########.fr       */
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
		current = current->next;
	}
}

void	print_cmds(t_list *cmds)
{
	t_list	*current;
	t_cmd	*cur_cmd;
	t_list	*cur_redir;
	t_redir	*redir;

	printf("CMDS:\n");
	while (cmds)
	{
		current = cmds;
		cur_cmd = (t_cmd *)current->content;
		printf("%s\n", cur_cmd->cmd[0]);
		printf("isbuiltin = %d\n", cur_cmd->is_builtin);
		cur_redir = cur_cmd->redirs;
		while (cur_redir)
		{
			redir = (t_redir *)cur_redir->content;
			printf("redir target = %s \n", redir->target);
			cur_redir = cur_redir->next;
		}
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
	t_list	*tokens;
	t_list	*cmd;
	t_env	*s_env;

	// int		exit_code;
	(void)argc;
	(void)argv;
	(void)envp;
	s_env = malloc(sizeof(t_env));
	if (!s_env)
		return (1);
	if (env_init(s_env, envp) == 1)
		return (free_s_env(s_env), 1);
	while (1)
	{
		buffer = readline("minishell> ");
		if (!buffer)
			break ;
		tokens = lexer(buffer);
		cmd = parsed_cmds(tokens);
		print_cmds(cmd);
		free_list(tokens);
		exit_code = call_exec(cmd, s_env);
		//free_cmds(cmd);
		if (*buffer)
			add_history(buffer);
		free(buffer);
	}
	free_s_env(s_env);
	return (0);
}
