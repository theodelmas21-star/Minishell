/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:57:00 by ssivilay          #+#    #+#             */
/*   Updated: 2026/01/30 18:55:29 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_readline(t_list *tokens)
{
	char	*buffer;

	{
		while (1)
		{
			buffer = readline("minishell> ");
			printf("buffer = %s\n", buffer);
			arg_to_token(buffer, tokens);
		}
	}
}
