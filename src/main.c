/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:50:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/15 17:09:19 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens(t_list *tokens)
{
	t_list	*current;
	t_token	*tok;

	current = tokens;
	while (current)
	{
		tok = (t_token *)current->content;
		printf("arg = %s | type = %d | quote = %d\n", tok->arg, tok->type, tok->quote_type);
		current = current->next;
	}
}

void	print_cmds(t_list *cmds)
{
	t_list *current;
	t_cmd	*cur_cmd;

	while (cmds)
	{
		current = cmds;
		cur_cmd = (t_cmd *)current->content;
		cmds = cmds->next;
		printf("%s", cur_cmd->cmd[0]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*buffer;
	int exit_code;
	t_list	*tokens;
	t_list	*cmd;

	(void)argc;
	(void)argv;
	while (1)
	{
		buffer = readline("minishell> ");
		if (!buffer)
			break ;
		tokens = lexer(buffer);
		cmd = token_to_cmd(tokens);
		free_list(tokens);
		exit_code = call_exec(cmd, envp);
		if (*buffer)
			add_history(buffer);
	}
	return (0);
}
