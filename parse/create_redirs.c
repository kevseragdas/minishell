#include "parse.h"
#include <unistd.h>
#include <stdlib.h>

static int	is_redir(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == HEREDOC);
}

void	find_redirs(t_cmds **cmd, t_tokens *tmp)
{
	t_redirs	*new_rdr;
	t_redirs	*curr_rdr;
	t_redirs	*head_rdr;

	head_rdr = NULL;
	curr_rdr = NULL;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redir(tmp->type) && tmp->next && tmp->next->type == WORD)
		{
			new_rdr = malloc(sizeof(t_redirs));
			if (!new_rdr)
				return ;
			new_rdr->type = tmp->type;
			new_rdr->target = ft_strdup(tmp->next->value);
			new_rdr->fd = -1;
			new_rdr->next = NULL;
			if (!head_rdr)
				head_rdr = new_rdr;
			else
				curr_rdr->next = new_rdr;
			curr_rdr = new_rdr;
		}
		tmp = tmp->next;
	}
	(*cmd)->redirs = head_rdr;
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