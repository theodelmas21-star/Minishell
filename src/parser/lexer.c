/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:55:36 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/02 16:15:37 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token_squote(char *buffer, int size)
{
	t_token *token;
	t_index ind;
	
	token = malloc(sizeof(t_token));
	token->arg = malloc(sizeof(char) * size);
	if (!token->arg)
		return (NULL);
	ind.i = 0;
	ind.j = 1;
	while (ind.j < size)
	{
		token->arg[ind.i] = buffer[ind.j];
		ind.i++;
		ind.j++;
	}
	token->arg[ind.i] = '\0';
	token->type = STRING;
	printf("token final : %s\n", token->arg);
	return (token);
}

int	handle_squote(char *buffer, t_state *state, t_list *tokens)
{
	t_index	index;

	index.i = 1;
	tokens = malloc(sizeof(t_token));
	while (buffer[index.i] != 39)
	{
		if (buffer[index.i] == '\0')
			return (-1);
		index.i++;
	}
	if (*state == STATE_GENERAL)
	{
		*state = STATE_IN_SQUOTE;
		tokens->content = create_token_squote(buffer, index.i);
	}
	/*if (state == STATE_IN_WORD)
	{
	}*/
	return (0);
}

void	state_machine(char *buffer, t_list *tokens)
{
	t_state	state;
	int		i;

	i = 0;
	state = STATE_GENERAL;
	if (!buffer)
		return ;
	while (buffer[i])
	{
		while (buffer[i] == ' ')
			i++;
		if (buffer[i] == 39)
		{
			if (handle_squote(buffer + i, &state, tokens) == -1)
				break ;
		}
		/*else if (buffer[i] == 34)
		i += handle_dquote(buffer + i, state, tokens);
	else
		i += handle_words(buffer + i, state, tokens);*/
		// tokens = tokens->next;
		i++;
	}
}
