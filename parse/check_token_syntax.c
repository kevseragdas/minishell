#include "parse.h"

static int	is_redir(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == HEREDOC);
}

static int	syntax_error(t_tokens **token)
{
	free_token_list(token);
	write(2, "minishell: syntax error near unexpected token\n", 46);
	return (258);
}

int	check_token_syntax(t_tokens **token)
{
	t_tokens	*tmp;

	tmp = *token;
	if (!tmp)
		return (0);
	if (tmp->type == PIPE)
		return (syntax_error(token));
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->prev || !tmp->next || tmp->next->type == PIPE)
				return (syntax_error(token));
		}
		if (is_redir(tmp->type))
		{
			if (!tmp->next || tmp->next->type != WORD)
				return (syntax_error(token));
		}
		tmp = tmp->next;
	}
	return (0);
}
