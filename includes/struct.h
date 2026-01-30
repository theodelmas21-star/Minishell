/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:00:56 by ssivilay          #+#    #+#             */
/*   Updated: 2026/01/30 18:42:49 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef enum e_token_type
{
	CMD,
	ARG,
	REDIRECT,
	PIPE,
	STRING
}					t_token_type;

typedef struct s_token
{
	char			*arg;
	t_token_type	type;
}					t_token;

typedef struct s_index
{
	int				i;
	int				j;
	int				k;
}					t_index;

#endif
