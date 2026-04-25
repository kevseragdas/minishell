#include "execute.h"

static int	run_parent(t_cmds **cmd, t_envp **env)
{
	int	backup_stdin;
	int	backup_stdout;
	int	status;

	backup_stdin = dup(STDIN_FILENO);
	backup_stdout = dup(STDOUT_FILENO);
	if (backup_stdin < 0 || backup_stdout < 0)
		return (perror("dup"), 1);
	if (redirections(*cmd) < 0)
	{
		dup2(backup_stdin, STDIN_FILENO);
		dup2(backup_stdout, STDOUT_FILENO);
		close(backup_stdin);
		close(backup_stdout);
		return (1);
	}
	status = exec_builtin(cmd, env, 1);
	fflush(stdout);
	dup2(backup_stdin, STDIN_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	close(backup_stdin);
	close(backup_stdout);
	return (status);
}

static int	run_child(t_cmds **cmd, t_envp **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
	{
		if (redirections(*cmd) < 0)
			exit(1);
		exec_external(*cmd, *env);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

int	execute_single(t_cmds **cmd, t_envp **env)
{
	if (!cmd || !*cmd)
		return (0);
	if (!(*cmd)->argv || !(*cmd)->argv[0])
	{
		if (redirections(*cmd) < 0)
			return (1);
		return (0);
	}
	if (is_builtin((*cmd)->argv[0]))
		return (run_parent(cmd, env));
	return (run_child(cmd, env));
}
