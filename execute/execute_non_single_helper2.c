#include "execute.h"

static void	child_process(t_cmds *cmd, t_envp **env, int prev_fd, int fd[2])
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_DFL);
	setup_pipe_input(prev_fd);
	setup_pipe_output(cmd, fd);
	if (redirections(cmd) < 0)
		exit(1);
	if (cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]))
		run_builtin_in_child(cmd, env);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	exec_external(cmd, *env);
	exit(1);
}

int	create_child(t_cmds *cmd, t_envp **env, int prev_fd, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		child_process(cmd, env, prev_fd, fd);
	return (pid);
}
