#include "parse.h"

static int	is_redir(t_token_type type)
{
	return (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == REDIR_APPEND
		|| type == HEREDOC);
}

static int	should_be_argv(t_tokens *tmp)
{
	if (!tmp || tmp->type != WORD)
		return (0);
	if (tmp->prev && is_redir(tmp->prev->type))
		return (0);
	if (tmp->value[0] == '\0')
		return (0);
	return (1);
}

static int	find_argv_num(t_tokens *tmp)
{
	int	argv_num;

	argv_num = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (should_be_argv(tmp))
			argv_num++;
		tmp = tmp->next;
	}
	return (argv_num);
}

static int	find_argv(t_cmds **cmd, t_tokens *tmp)
{
	int	i;
	int	argv_num;

	i = 0;
	argv_num = find_argv_num(tmp);
	(*cmd)->argv = malloc(sizeof(char *) * (argv_num + 1));
	if (!(*cmd)->argv)
		return (1);
	while (tmp && tmp->type != PIPE)
	{
		if (should_be_argv(tmp))
		{
			(*cmd)->argv[i] = ft_strdup(tmp->value);
			if (!(*cmd)->argv[i])
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	(*cmd)->argv[i] = NULL;
	return (0);
}

t_cmds	*create_cmd_list(t_tokens *tmp)
{
	t_cmds		*cmd;
	t_tokens	*pipe_ptr;

	cmd = malloc(sizeof(t_cmds));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	find_redirs(&cmd, tmp);
	if (find_argv(&cmd, tmp))
	{
		free_redirs(&cmd->redirs);
		free(cmd);
		return (NULL);
	}
	pipe_ptr = tmp;
	while (pipe_ptr && pipe_ptr->type != PIPE)
		pipe_ptr = pipe_ptr->next;
	if (pipe_ptr && pipe_ptr->next)
		cmd->next = create_cmd_list(pipe_ptr->next);
	return (cmd);
}
