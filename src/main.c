/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:50:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/04 14:58:30 by ssivilay         ###   ########.fr       */
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
		printf("arg = %s | type = %d\n", tok->arg, tok->type);
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
		free(buffer);
	}
	return (0);
}
