#include "parse.h"

static int	is_redir(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == HEREDOC);
}

static t_redirs	*create_redirection(t_token_type type, char *target)
{
	t_redirs	*new;

	new = malloc(sizeof(t_redirs));
	if (!new)
		return (NULL);
	new->type = type;
	new->target = ft_strdup(target);
	new->fd = -1;
	new->next = NULL;
	return (new);
}

void	find_redirs(t_cmds **cmd, t_tokens *tmp)
{
	t_redirs	*new;
	t_redirs	*curr;
	t_redirs	*head;

	head = NULL;
	curr = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redir(tmp->type) && tmp->next && tmp->next->type == WORD)
		{
			new = create_redirection(tmp->type, tmp->next->value);
			if (!new)
				return ;
			if (!head)
				head = new;
			else
				curr->next = new;
			curr = new;
		}
		tmp = tmp->next;
	}
	(*cmd)->redirs = head;
}

void	free_redirs(t_redirs **redir)
{
	t_redirs	*tmp;

	while (*redir)
	{
		tmp = *redir;
		if (tmp->fd != -1)
			close(tmp->fd);
		free(tmp->target);
		*redir = (*redir)->next;
		free(tmp);
	}
}
