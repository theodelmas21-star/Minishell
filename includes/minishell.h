/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:59:14 by ssivilay          #+#    #+#             */
/*   Updated: 2026/03/09 14:48:09 by tdelmas2         ###   ########.fr       */
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

// signals
void			init_signal(void);
void			reset_signals(void);

// expand
int				expander(t_list *cmds, t_env *s_env, int exit_code);
int				call_exp_env(t_cmd *cmd, t_env *s_env, int i);
int				expand_cmd(t_cmd *cmd, t_env *s_env, int exit_code);
char			*expand_hd(char *res, t_env *s_env, t_exec exc);

// exec
void			error(char *error_message);
int				size_cmd(t_list *cmds);
char			*find_cmd_path(t_env *envp, t_cmd *cmd);
t_env			*find_path(t_env *envp);
int				call_exec(t_list *cmds, t_env *s_env, t_exec exc);
int	apply_redirections(t_cmd *cmds, t_env *s_env, t_exec exc);
int				apply_all_redirs(t_redir redir_R, t_env *s_env, t_exec exc);
int				env_init(t_env *s_env, char **envp);
int	exec_builtin_cmd(t_list *cmds, t_env *s_env, t_exec exc);
int	prep_exec(t_list *cmds, t_env *s_env);
int	find_all_cmd_path(t_list *cmds, t_env *env);


// built-in
int				simple_export(t_env *s_env);
int				concat_or_replace(t_index index, t_cmd *cmd, t_env *s_env);
int				is_concatenate(char *cmd);
int				echo(t_cmd *cmd);
int				pwd(t_cmd *cmd);
int				export(t_cmd *cmd, t_env *s_env);
int				env(t_env *s_env);
int				handle_builtins(t_cmd *cmd, t_env *s_env, int pid);
int				unset(t_cmd *cmd, t_env *s_env);
int				cd(t_cmd *cmd, t_env *s_env);
void			is_exit(t_list *cmd, t_env *s_env, int exit_code);
char *remove_concat_operator(char *cmd);

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
