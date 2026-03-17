#include "execute.h"

static void	read_heredoc(char *delimiter, int write_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
}

int	handle_heredoc(t_redirs *redir)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) < 0)
		return (perror("pipe"), -1);
	
	// Fork'tan ÖNCE okumayı bekleyecek olan prosesi korumaya alıyoruz!
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); // Okuma yapan çocuk anında ölebilir
		signal(SIGQUIT, SIG_IGN);
		close(fd[0]);
		read_heredoc(redir->target, fd[1]);
		exit(0);
	}
	close(fd[1]);
	
	waitpid(pid, &status, 0);
	set_signals_executing();
	
	// Eğer çocuk Ctrl+C ile öldüyse işlemi iptal et
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		return (close(fd[0]), -1);
	}
	if (dup2(fd[0], STDIN_FILENO) < 0)
		return (close(fd[0]), -1);
	close(fd[0]);
	return (0);
}