/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:59:14 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/04 11:28:19 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "libraries.h"
# include "struct.h"

// lexer
t_list	*lexer(char *input);
void	lexer_states(t_lexer *lexer, char c);
void	add_char_to_tmp(t_lexer *lexer, char c);
void	create_token(t_lexer *lexer);

// utils
void	free_tab(char **tab);

#endif
