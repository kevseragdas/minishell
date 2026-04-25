#include "execute.h"

static void	read_heredoc(char *delimiter, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

int	handle_heredoc(t_redirs *redir)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (!redir || !redir->target)
		return (-1);
	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fd[0]), close(fd[1]), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
		close(fd[0]);
		read_heredoc(redir->target, fd[1]);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (close(fd[0]), write(1, "\n", 1), -1);
	redir->fd = fd[0];
	return (0);
}

int	prepare_heredocs(t_cmds *cmd)
{
	t_redirs	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (redir->fd != -1)
				{
					close(redir->fd);
					redir->fd = -1;
				}
				if (handle_heredoc(redir) < 0)
					return (-1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
