/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:50:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/25 20:30:57 by ssivilay         ###   ########.fr       */
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

	printf("CMDS:\n");
	while (cmds)
	{
		current = cmds;
		cur_cmd = (t_cmd *)current->content;
		cmds = cmds->next;
		printf("%s\n", cur_cmd->cmd[0]);
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

	// int		exit_code;
	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		buffer = readline("minishell> ");
		if (!buffer)
			break ;
		tokens = lexer(buffer);
		print_tokens(tokens);
		cmd = parsed_cmds(tokens);
		print_cmds(cmd);
		free_list(tokens);
		// exit_code = call_exec(cmd, envp);
		// free_cmds(cmd);
		if (*buffer)
			add_history(buffer);
		free(buffer);
	}
	return (0);
}
