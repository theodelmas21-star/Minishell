/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelmas2 <tdelmas2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:00:56 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/20 15:44:09 by tdelmas2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_HEREDOC, //<<
	REDIR_APPEND,  //>>
	REDIR_IN,      // <
	REDIR_OUT      // >
}					t_token_type;

typedef struct s_redir
{
	t_token_type	type;
	char *target; // fichier ou delimiter
	char			*LIMITER;
	int fd; // STDIN ou STDOUT
}					t_redir;

typedef enum e_state
{
	STATE_GENERAL,
	STATE_IN_WORD,
	STATE_IN_SQUOTE,
	STATE_IN_DQUOTE
}					t_state;

typedef struct s_cmd
{
	char **cmd;     // {"ls", "-l", NULL}
	t_list *redirs; // < > >> <<
	int				is_builtin;
	int				pipefd[2];
}					t_cmd;

typedef struct s_env
{
	char			**env;
	char			*path;
	char			**path_split;
}					t_env;

typedef enum e_quote
{
	NO_QUOTE,
	SQUOTE,
	DQUOTE,
}					t_quote;

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

#endif
