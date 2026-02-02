/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:57:00 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/02 14:21:39 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_readline(t_list *tokens)
{
	char	*buffer;

	while (1)
	{
		buffer = readline("minishell> ");
		printf("buffer = %s\n", buffer);
		state_machine(buffer, tokens);
		// arg_to_token(buffer, tokens);
	}
}
