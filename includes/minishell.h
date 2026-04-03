/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 13:59:14 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/03 09:31:54 by tdelmas2         ###   ########.fr       */
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
t_list			*parsed_cmds(t_list *tokens, int *exit_code);
int				check_args(t_list *tokens);
t_list			*token_to_cmd(t_list *tokens);
t_cmd			*init_cmd(void);
int				cmd_add_arg(t_cmd *cmd, char *arg, t_quote qt, int is_new);
int				is_redirection(t_token_type type);
int				is_builtin(char *cmd);
int				is_subarg(int curr_subarg, int next_subarg);

// signals
void			init_signal(void);
void			reset_signals(void);

// expand
int				expander(t_list *cmds, t_env *s_env, int exit_code);
char			*call_exp_env(char *cmd, t_env *s_env);
int				expand_cmd(t_cmd *cmd, t_env *s_env, int exit_code);
char			*expand_hd(char *res, t_env *s_env, t_exec *exc,
					int is_newline);
int				is_expand(t_cmd *cmd, int ind_cmd);
char			*expand_all(t_cmd *cmd, t_env *s_env, int exit_code, int str);
int				is_env(char *cmd, t_env *s_env);
char			*interrogation(char *cmd, int exit_code);
int				handle_export_arg(t_cmd *cmd, t_env *s_env, int arg_idx);
int				get_var_name_len(char *var);
int				check_var_in_env(char *var, char **env, int var_len);
char			**join_split(int str, t_cmd *cmd);
int				len_new(char *str, int ind_str);
int				is_expandable(char *str);
char			*handle_number(char *new);
char			**without_null(char **cmd, int i);
void adapt_data_null(int pos, t_cmd *cmd);

// exec
int				size_cmd(t_list *cmds);
char			*find_cmd_path(t_env *envp, t_cmd *cmd);
int				is_directory(char *path);
t_env			*find_path(t_env *envp);
int				call_exec(t_list *cmds, t_env *s_env, t_exec exc);
int				apply_redirections(t_cmd *cmds, t_env *s_env, t_exec exc);
int				apply_all_redirs(t_redir redir_R, t_env *s_env, t_exec exc);
int				env_init(t_env *s_env, char **envp);
int				exec_builtin_cmd(t_list *cmds, t_env *s_env, t_exec exc);
int				find_all_cmd_path(t_list *cmds, t_env *env);
char			**join_sub_args(t_cmd *cmd);
int	secur_fork(t_list *cmds, t_cmd *current, int pid);
int	pipe_exec(t_list *cmds, t_env *s_env, int *pid, t_exec *exc);
void close_fds(t_list *cmds, t_exec *exc, t_cmd *current);
void	child_exec(t_list *cmds, t_env *s_env, t_exec *exc, t_list *head);
void start_child(t_exec *exc);
void builtins_in_child(t_cmd *current, t_list *head, t_env *s_env, t_exec *exc);

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
int				is_exit(t_cmd *cmd, t_list *cmds, t_env *s_env,
					t_exit_args exit_args);
char			*remove_concat_operator(char *cmd);
int				parser_export(char *cmd);
int				handle_export_arg(t_cmd *cmd, t_env *s_env, int arg_idx);
int				process_var_new(t_cmd *cmd, t_env *s_env, int arg_idx);
int				process_var_exists(t_cmd *cmd, t_env *s_env, int arg_idx,
					int var_idx);
int				check_var_in_env(char *var, char **env, int var_len);
int				get_var_name_len(char *var);
int				create_var(char *var, t_env *s_env);
int stop_hd(char *tmp, t_redir *redir_R);

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
void			print_cmds(t_list *cmds);
void free_tab_cmd(t_cmd *cmd);
void free_tab_rest_cmd(char **old, int len);
void free_all_exit(t_list *head, t_env *s_env, int res);

#endif
