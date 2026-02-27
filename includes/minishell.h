/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:59:14 by ssivilay          #+#    #+#             */
/*   Updated: 2026/03/09 14:36:32 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../GNL/get_next_line.h"
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
t_list			*parsed_cmds(t_list *tokens);
int				check_args(t_list *tokens);
t_list			*token_to_cmd(t_list *tokens);
int				is_redirection(t_token_type type);
// exec
void			error(char *error_message);
int				size_cmd(t_list *cmds);
char			*find_cmd_path(t_env *envp, t_cmd *cmd);
t_env			*find_path(t_env *envp);
int				call_exec(t_list *cmds, t_env *s_env);
void			apply_redirections(t_cmd *cmds);
int				env_init(t_env *s_env, char **envp);

// built-in
int				simple_export(t_env *s_env);
int				concat_or_replace(t_index index, t_cmd *cmd, t_env *s_env);
int				is_concatenate(char *cmd);
int				echo(t_cmd *cmd);
int				pwd(t_cmd *cmd);
int				export(t_cmd *cmd, t_env *s_env);
int				env(t_env *s_env);
int				handle_builtins(t_cmd *cmd, t_env *s_env, int pid);
int unset(t_cmd *cmd, t_env *s_env);


// utils
void			free_tab(char **tab);
void			free_list(t_list *list);
void			free_cmds(t_list *cmds);
void			free_cmd(t_cmd *cmd);
void			free_s_env(t_env *s_env);
char			*ft_strjoin_free(char *str, char *str2, char *str_to_free);
char			*ft_strjoin_free_both(char *str, char *str2);
int				env_init(t_env *s_env, char **envp);
void			del_token(void *content);
int				is_space(char c);
int				is_operator(char c);
void			print_env(char **env);

#endif
