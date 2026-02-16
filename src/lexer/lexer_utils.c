/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:48:55 by ssivilay          #+#    #+#             */
/*   Updated: 2026/02/16 16:50:43 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	add_char_to_tmp(t_lexer *lexer, char c)
{
	char	*new_tmp;
	int		len;

	if (!lexer->tmp)
		len = 0;
	else
		len = ft_strlen(lexer->tmp);
	new_tmp = malloc(len + 2);
	if (!new_tmp)
		return ;
	if (lexer->tmp)
	{
		ft_strlcpy(new_tmp, lexer->tmp, len + 1);
		free(lexer->tmp);
	}
	new_tmp[len] = c;
	new_tmp[len + 1] = '\0';
	lexer->tmp = new_tmp;
}

t_token_type	get_token_type(char *arg)
{
	if (ft_strncmp(arg, "|", 1) == 0 && ft_strlen(arg) == 1)
		return (PIPE);
	else if (ft_strncmp(arg, "<<", 2) == 0 && ft_strlen(arg) == 2)
		return (REDIR_HEREDOC);
	else if (ft_strncmp(arg, ">>", 2) == 0 && ft_strlen(arg) == 2)
		return (REDIR_APPEND);
	else if (ft_strncmp(arg, "<", 1) == 0 && ft_strlen(arg) == 1)
		return (REDIR_IN);
	else if (ft_strncmp(arg, ">", 1) == 0 && ft_strlen(arg) == 1)
		return (REDIR_IN);
	else
		return (WORD);
}

void	create_token(t_lexer *lexer, t_quote quote_type)
{
	
/* 	t_token	*token;
	int		count_tmp;
	int		i;
	int		j;
	int		k;
	char	**tmp;

	// t_list	*node;
	(void)quote_type;
	printf("lexer->tmp == %s\n", lexer->tmp);
	count_tmp = 0;
	if (!lexer->tmp || !lexer->tmp[0])
		return ;
	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	i = 0;
	while (lexer->tmp[i])
	{
		if (lexer->tmp[i] == '\'')
		{
			j = 0;
			while (lexer->tmp[i + j + 1] && lexer->tmp[i + j + 1] != '\'')
				j++;
			count_tmp++;
			i += j + 1;
		}
		else if (lexer->tmp[i] == '\"')
		{
			j = 0;
			while (lexer->tmp[i + j + 1] && lexer->tmp[i + j + 1] != '\"')
				j++;
			count_tmp++;
			i += j + 1;
		}
		else
		{
			j = 0;
			while (lexer->tmp[i + j] && lexer->tmp[i + j] != '\''
				&& lexer->tmp[i + j] != '\"')
				j++;
			count_tmp++;
			i += j;
		}
		i++;
	}
	tmp = ft_calloc(sizeof(char *), count_tmp + 1);
	i = 0;
	k = 0;
	while (lexer->tmp[i])
	{
		if (lexer->tmp[i] == '\'')
		{
			j = 0;
			while (lexer->tmp[i + j + 1] && lexer->tmp[i + j + 1] != '\'')
				j++;
			tmp[k] = ft_calloc(sizeof(char), j + 1);
			i++;
			ft_strlcpy(tmp[k], &lexer->tmp[i], j + 1);
			k++;
			i += j + 1;
		}
		else if (lexer->tmp[i] == '\"')
		{
			j = 0;
			while (lexer->tmp[i + j + 1] && lexer->tmp[i + j + 1] != '\"')
				j++;
			tmp[k] = ft_calloc(sizeof(char), j + 1);
			i++;
			ft_strlcpy(tmp[k], &lexer->tmp[i], j + 1);
			k++;
			i += j + 1;
		}
		else
		{
			j = 0;
			while (lexer->tmp[i + j] && lexer->tmp[i + j] != '\''
				&& lexer->tmp[i + j] != '\"')
				j++;
			tmp[k] = ft_calloc(sizeof(char), j + 1);
			ft_strlcpy(tmp[k], &lexer->tmp[i], j + 1);
			k++;
			i += j - 1;
		}

	}
	printf("tmp[0] = %s\n", tmp[0]);
	printf("tmp[1] = %s\n", tmp[1]); */
	/* 	node = ft_lstnew(token);
		ft_lstadd_back(&lexer->tokens, node);
		lexer->tmp = NULL; */
}
