/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:55:36 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/02 17:05:35 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token_squote(char *buffer, int size)
{
	t_token	*token;
	t_index	ind;

	token = malloc(sizeof(t_token));
	token->arg = malloc(sizeof(char) * size);
	if (!token->arg)
		return (NULL);
	ind = (t_index){0,1,0};
	while (ind.j < size)
	{
		token->arg[ind.i] = buffer[ind.j];
		ind.i++;
		ind.j++;
	}
	token->arg[ind.i] = '\0';
	token->type = STRING;
	printf(" token->arg : %s\n", token->arg);
	return (token);
}

void	join_token_squote(t_token *content, char *buffer, int size)
{
	t_index	index;
	char	*tmp;
	char	*prev_content;

	tmp = malloc(sizeof(char) * size);
	if (!tmp)
		return ;
	index = (t_index){0,1,0};
	while (index.j < size)
	{
		tmp[index.i] = buffer[index.j];
		index.i++;
		index.j++;
	}
	tmp[index.i] = '\0';
	prev_content = content->arg;
	content->arg = ft_strjoin(content->arg, tmp);
	free(prev_content);
	free(tmp);
	printf(" content->arg : %s\n", content->arg);
	return ;
}

int	handle_squote(char *buffer, t_state *state, t_list *tokens)
{
	t_index	index;

	index = (t_index){1,0,0};
	tokens = malloc(sizeof(t_token));
	while (buffer[index.i] != 39)
	{
		if (buffer[index.i] == '\0')
			return (-1);
		index.i++;
	}
	if (*state == STATE_GENERAL)
	{
		tokens->content = create_token_squote(buffer, index.i);
	}
	if (*state == STATE_IN_WORD)
	{
		join_token_squote(tokens->content, buffer, index.i);
	}
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
		if (buffer[i] == '\'')
		{
			if (handle_squote(buffer + i, &state, tokens) == -1)
				break ;
		}
		/*else if (buffer[i] == '\"')
		i += handle_dquote(buffer + i, state, tokens);
	else
		i += handle_words(buffer + i, state, tokens);*/
		// tokens = tokens->next;
		i++;
	}
}
