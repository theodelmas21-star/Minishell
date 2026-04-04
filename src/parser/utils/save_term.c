/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 17:01:03 by tdelmas2          #+#    #+#             */
/*   Updated: 2026/04/04 17:07:04 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	save_term(t_exec *exc)
{
	tcgetattr(STDIN_FILENO, &exc->term_backup);
}

void	restore_term(t_exec *exc)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &exc->term_backup);
}
