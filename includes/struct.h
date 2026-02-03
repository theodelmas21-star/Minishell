/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:00:56 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/03 15:12:41 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef enum e_token_type
{
	WORD,
	PIPE,         // |
	HEREDOC,      //<<
	REDIR_APPEND, //>>
	REDIR_IN,     // <
	REDIR_OUT     // >
}					t_token_type;

typedef enum e_state
{
	STATE_GENERAL,
	STATE_IN_WORD,
	STATE_IN_SQUOTE,
	STATE_IN_DQUOTE
}					t_state;

typedef enum e_lexer_flag
{
	IN_TOKEN,
	END_TOKEN,
	ERROR
}					t_lexer_flag;

typedef struct s_token
{
	char			*arg;
	t_token_type	type;
}					t_token;

typedef struct s_lexer
{
	char			*input;
	int				i;
	char			curr_char;
	t_state			state;
	char			*tmp;
	t_list			*tokens;
	t_lexer_flag	flag;
}					t_lexer;

typedef struct s_index
{
	int				i;
	int				j;
	int				k;
}					t_index;

#endif
