#include "execute.h"

static int	redir_in(t_redirs *redir)
{
	int	fd;

	fd = open(redir->target, O_RDONLY);
	if (fd < 0)
	{
		perror(redir->target);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	redir_out(t_redirs *redir)
{
	int	fd;

	fd = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(redir->target);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	redir_append(t_redirs *redir)
{
	int	fd;

	fd = open(redir->target, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(redir->target);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	redir_heredoc(t_redirs *redir)
{
	if (redir->fd == -1)
		return (-1);
	if (dup2(redir->fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(redir->fd);
		redir->fd = -1;
		return (-1);
	}
	close(redir->fd);
	redir->fd = -1;
	return (0);
}

int	redirections(t_cmds *cmd)
{
	t_redirs	*redir;
	int			status;

	if (!cmd)
		return (0);
	redir = cmd->redirs;
	while (redir)
	{
		status = 0;
		if (redir->type == REDIR_IN)
			status = redir_in(redir);
		else if (redir->type == REDIR_OUT)
			status = redir_out(redir);
		else if (redir->type == REDIR_APPEND)
			status = redir_append(redir);
		else if (redir->type == HEREDOC)
			status = redir_heredoc(redir);
		if (status != 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
