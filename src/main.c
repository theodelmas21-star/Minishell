/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:50:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/09 13:24:18 by ssivilay         ###   ########.fr       */
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
	t_list	*current;
	t_cmd	*cmd;

	current = cmds;
	while (current)
	{
		cmd = (t_cmd *)current->content;
		printf("arg = %s\n", cmd->cmd[0]);
		current = current->next;
	}
}

int	main(void)
{
	char	*buffer;
	t_list	*tokens;

	while (1)
	{
		buffer = readline("minishell> ");
		if (!buffer)
			break ;
		tokens = lexer(buffer);
		print_tokens(tokens);
		//token_to_cmd(tokens);
		free(buffer);
	}
	return (0);
}
