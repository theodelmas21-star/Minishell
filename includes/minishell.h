/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:59:14 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/09 11:45:13 by ssivilay         ###   ########.fr       */
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
void	create_token(t_lexer *lexer, t_quote quote_type);
int		is_space(char c);
int		is_operator(char c);

// parser
t_list	*token_to_cmd(t_list *tokens);

// exec
char	*find_cmd_path(t_env *envp, t_cmd *cmd);
t_cmd	*find_path(t_env *envp);

// utils
void	free_tab(char **tab);

#endif
