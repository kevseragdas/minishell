#include "execute.h"

//static void	read_heredoc(char *delimiter, int write_fd)
static void	read_heredoc(char *delimiter, int write_fd, t_cmds **cmd, t_envp **env)
{
	char	*line;
	int		line_count;

	line_count = 1;
	while (1)
	{
		line = readline("> ");
		line_count++;
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document at line ", 2);
			ft_putnbr_fd(line_count, 2);
			ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
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
	free_cmd_list(cmd);
	free_envp_list(env);
	exit(0);
}

//int	handle_heredoc(t_redirs *redir)
static int	handle_heredoc(t_redirs *redir, t_cmds **cmd, t_envp **env)
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
		set_signals_heredoc();
		close(fd[0]);
		read_heredoc(redir->target, fd[1], cmd, env);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	set_signals_interactive();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(fd[0]), -1);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (close(fd[0]), -1);
	redir->fd = fd[0];
	return (0);
}

//int	prepare_heredocs(t_cmds *cmd)
int	prepare_heredocs(t_cmds **cmd, t_envp **env)
{
	t_redirs	*redir;
	t_cmds		*tmp;

	tmp = *cmd;
	while (tmp)
	{
		redir = tmp->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				if (redir->fd != -1)
				{
					close(redir->fd);
					redir->fd = -1;
				}
				if (handle_heredoc(redir, cmd, env) < 0)
					return (-1);
			}
			redir = redir->next;
		}
		tmp = tmp->next;
	}
	return (0);
}