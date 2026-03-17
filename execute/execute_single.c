#include "execute.h"

int	run_parent(t_cmds **cmd, t_envp **env)
{
	int	backup_stdin;
	int	backup_stdout;
	int	status;

	backup_stdin = dup(STDIN_FILENO);
	backup_stdout = dup(STDOUT_FILENO);
	if (redirections(*cmd) < 0)
	{
		dup2(backup_stdin, STDIN_FILENO);
		dup2(backup_stdout, STDOUT_FILENO);
		close(backup_stdin);
		close(backup_stdout);
		return (1);
	}
	status = exec_builtin(cmd, env, 1);
	dup2(backup_stdin, STDIN_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	close(backup_stdin);
	close(backup_stdout);
	return (status);
}

int	run_child(t_cmds **cmd, t_envp **env)
{
	pid_t	pid;
	int		status;

	// SİHİR BURADA: Fork'tan ÖNCE ana prosesi korumaya alıyoruz!
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		// Çocuk proses kendi sinyallerini yeniden ayarlıyor
		set_signals_executing();
		if (redirections(*cmd) < 0)
			exit(1);
		exec_external(*cmd, *env);
		perror("minishell");
		exit(1);
	}
	waitpid(pid, &status, 0);
	set_signals_interactive();
	
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	execute_single(t_cmds **cmd, t_envp **env)
{
	if (is_builtin((*cmd)->argv[0]))
		return (run_parent(cmd, env));
	else
		return (run_child(cmd, env));
}