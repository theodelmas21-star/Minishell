/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:50:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/10 11:14:32 by tdelmas2         ###   ########.fr       */
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

void	print_cmds(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd[i])
	{
		printf("cmd = %s\n", cmd->cmd[i++]);
	}
}

int	main(void)
{
	char	*buffer;
	t_list	*tokens;
	t_cmd	*cmd;

	while (1)
	{
		buffer = readline("minishell> ");
		if (!buffer)
			break ;
		tokens = lexer(buffer);
		print_tokens(tokens);
		cmd = token_to_cmd(tokens);
		print_cmds(cmd);
		free(buffer);
	}
	return (0);
}
