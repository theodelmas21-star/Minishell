/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:00:56 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/04 17:17:31 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_HEREDOC,
	REDIR_APPEND,
	REDIR_IN,
	REDIR_OUT
}					t_token_type;

typedef enum e_state
{
	STATE_GENERAL,
	STATE_IN_WORD,
	STATE_IN_SQUOTE,
	STATE_IN_DQUOTE
}					t_state;

typedef enum e_quote
{
	NO_QUOTE,
	SQUOTE,
	DQUOTE,
}					t_quote;

typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	char			*delimiter;
	int				exp_hd;
	int				fd;
}					t_redir;

typedef struct s_cmd
{
	char			**cmd;
	t_list			*redirs;
	int				is_builtin;
	int				pipefd[2];
	int				*is_expand;
	int				*sub_args;
	int				*quote_type;
	int				cmd_error;
}					t_cmd;

typedef struct s_env
{
	char			**env;
	char			*path;
	char			**path_split;
}					t_env;

typedef struct s_token
{
	t_list			*subtokens;
	char			*arg;
	t_token_type	type;
	t_quote			quote_type;
}					t_token;

typedef struct s_lexer
{
	char			*input;
	int				i;
	t_state			state;
	t_state			prev_state;
	int				in_sequence;
	char			*tmp;
	t_list			*tokens;
}					t_lexer;

typedef struct s_index
{
	int				i;
	int				j;
	int				k;
}					t_index;

typedef struct s_exec
{
	int				prev_fd;
	int				exit_code;
	int				error;
	int				saved_stdin;
	int				saved_stdout;
	struct termios	term_backup;
}					t_exec;

typedef struct s_exit_args
{
	t_exec			*exc;
	int				exit_code;
	int				in_pipe;
}					t_exit_args;

typedef struct s_sub_args_helper
{
	int				*new;
	t_index			*index;
	int				len;
	int				pos;
}					t_sub_args_helper;

typedef struct s_expand_helper
{
	t_cmd			*cmd;
	t_env			*s_env;
	int				exit_code;
	int				str;
}					t_expand_helper;

typedef struct s_heredoc_helper
{
	t_list			*cur_cmd;
	t_list			*cur_redir;
	t_cmd			*cmd;
	t_redir			*redir;
}					t_hd_helper;

#endif
