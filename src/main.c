/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:50:00 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/02/05 11:56:11 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*buffer;

	buffer = NULL;
	while (1)
	{
		buffer = readline("minishell> ");
		lexer(buffer);
	}
	return (0);
}
