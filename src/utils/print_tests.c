/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssivilay <ssivilay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:03:42 by ssivilay          #+#    #+#             */
/*   Updated: 2026/04/03 15:17:10 by ssivilay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tokens(t_list *tokens)
{
	t_list	*current;
	t_token	*tok;
	t_list	*curr_sub;
	t_token	*subtok;

	current = tokens;
	while (current)
	{
		tok = (t_token *)current->content;
		printf("TOKEN:\n");
		printf("  arg = %s | type = %d | quote = %d\n", tok->arg, tok->type,
			tok->quote_type);
		curr_sub = tok->subtokens;
		while (curr_sub)
		{
			subtok = (t_token *)curr_sub->content;
			printf("    SUBTOKEN: arg = %s | type = %d | quote = %d\n",
				subtok->arg, subtok->type, subtok->quote_type);
			curr_sub = curr_sub->next;
		}
		printf("\n");
		current = current->next;
	}
}

void	print_cmd_content(int i, t_cmd *cur_cmd)
{
	printf("%s\n", cur_cmd->cmd[i]);
	printf("is_expand[%d] = %d\n", i, cur_cmd->is_expand[i]);
	printf("subarg[%d] = %d\n", i, cur_cmd->sub_args[i]);
	printf("quote_type[%d] = %d\n", i, cur_cmd->quote_type[i]);
	printf("----\n");
}

void	print_redir_content(t_redir *redir)
{
	printf("redir target = %s \n", redir->target);
	printf("tok type = %u \n", redir->type);
	printf("delimiter = %s \n", redir->delimiter);
	printf("exp hd = %d \n", redir->exp_hd);
	printf("fd = %d \n", redir->fd);
}

void	print_cmds(t_list *cmds)
{
	t_list	*current;
	t_cmd	*cur_cmd;
	t_list	*cur_redir;
	t_redir	*redir;
	int		i;

	while (cmds)
	{
		i = 0;
		current = cmds;
		cur_cmd = (t_cmd *)current->content;
		while (cur_cmd->cmd[i])
		{
			print_cmd_content(i, cur_cmd);
			i++;
		}
		cur_redir = cur_cmd->redirs;
		while (cur_redir)
		{
			redir = (t_redir *)cur_redir->content;
			print_redir_content(redir);
			cur_redir = cur_redir->next;
		}
		cmds = cmds->next;
	}
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		printf("envp is NULL");
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
