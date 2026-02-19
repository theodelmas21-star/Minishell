/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:59:14 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/19 17:56:23 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "libraries.h"
# include "struct.h"

// lexer
t_list			*lexer(char *input);
void			lexer_states(t_lexer *lexer, char c);
void			add_char_to_tmp(t_lexer *lexer, char c);
t_token_type	get_token_type(char *arg);
void			handle_operator(t_lexer *lexer, char c);
void			handle_squotes(t_lexer *lexer, char c);
void			handle_dquotes(t_lexer *lexer, char c);
void			handle_word(t_lexer *lexer, char c);
void			create_token(t_lexer *lexer, t_quote quote_type);
void			create_subtoken(t_lexer *lexer, t_quote quote_type);
void			on_create_token(t_lexer *lexer, t_quote quote_type,
					int in_sequence);
int				is_space(char c);
int				is_operator(char c);

// parser
t_list			*token_to_cmd(t_list *tokens);

// exec
char			*find_cmd_path(t_env *envp, t_cmd *cmd);
t_env			*find_path(t_env *envp);
void			call_exec(t_list *cmds, char **envp);

// utils
void			free_tab(char **tab);
void			free_list(t_list *list);
void			free_cmds(t_list *cmds);
void			del_token(void *content);
int				is_space(char c);
int				is_operator(char c);

#endif
