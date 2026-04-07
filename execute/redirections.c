#include "execute.h"

static int	print_error(char *file)
{
	write(2, "minishell: ", 11);
	perror(file);
	return (1);
}

int	redir_in(t_redirs *redir)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd < 0)
		return (print_error(redir->target));
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		close(fd);
		return (print_error("dup2"));
	}
	close(fd);
	return (0);
}

int	redir_out(t_redirs *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (print_error(redir->target));
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (print_error("dup2"));
	}
	close(fd);
	return (0);
}

int	redir_append(t_redirs *redir)
{
	int	fd;

	fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (print_error(redir->target));
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (print_error("dup2"));
	}
	close(fd);
	return (0);
}

int	redirections(t_cmds *cmd)
{
	t_redirs	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN)
		{
			if (redir_in(redir))
				return (1);
		}
		else if (redir->type == REDIR_OUT)
		{
			if (redir_out(redir))
				return (1);
		}
		else if (redir->type == REDIR_APPEND)
		{
			if (redir_append(redir))
				return (1);
		}
		else if (redir->type == HEREDOC)
		{
			if (handle_heredoc(redir))
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}