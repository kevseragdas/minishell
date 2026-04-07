#include "execute.h"

static void	handle_child(t_cmds *cmd, t_envp **env, int prev_fd, int fd[2])
{
	int	redir_status;

	set_signals_executing();

	// 🔹 stdin (önceki pipe)
	if (prev_fd != STDIN_FILENO)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}

	// 🔥 1. REDIRECTION ÖNCE
	redir_status = redirections(cmd);
	if (redir_status != 0)
		exit(redir_status);

	// 🔥 2. PIPE SONRA
	if (cmd->next)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
	}

	// 🔥 3. EXEC
	if (is_builtin(cmd->argv[0]))
		exit(exec_builtin(&cmd, env, 0));

	exec_external(cmd, *env);
	exit(1);
}

static int	wait_processes(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		final_status;

	final_status = 1;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				final_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
					write(1, "\n", 1);
				else if (WTERMSIG(status) == SIGQUIT)
					write(1, "Quit (core dumped)\n", 19);
				final_status = 128 + WTERMSIG(status);
			}
		}
	}
	set_signals_interactive();
	return (final_status);
}

int	execute_non_single(t_cmds *cmd, t_envp **env)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = STDIN_FILENO;
	while (cmd)
	{
		if (cmd->next && pipe(fd))
			return (perror("pipe"), 1);
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
			handle_child(cmd, env, prev_fd, fd);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		if (cmd->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		cmd = cmd->next;
	}
	return (wait_processes(pid));
}