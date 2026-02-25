#include "../../includes/minishell.h"

int is_redirection(t_token_type type)
{
	if (type == REDIR_IN || type == REDIR_OUT || type == REDIR_APPEND 
		|| type == REDIR_HEREDOC)
		return (1);
	else
		return (0);
}
