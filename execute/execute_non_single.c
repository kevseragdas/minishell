#include "execute.h"

static t_envp	*clone_env_list(t_envp *env)
{
	t_envp	*head;
	t_envp	*tail;
	t_envp	*new_node;

	head = NULL;
	tail = NULL;
	while (env)
	{
		new_node = malloc(sizeof(t_envp));
		if (!new_node)
			return (free_envp_list(&head), NULL);
		new_node->key = ft_strdup(env->key);
		new_node->value = env->value ? ft_strdup(env->value) : NULL;
		new_node->next = NULL;
		if (!new_node->key || (env->value && !new_node->value))
			return (free(new_node->key), free(new_node->value),
				free(new_node), free_envp_list(&head), NULL);
		if (!head)
			head = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		env = env->next;
	}
	return (head);
}

static int	is_env_modifying_builtin(char *name)
{
	if (!name)
		return (0);
	if (!ft_strcmp(name, "export"))
		return (1);
	if (!ft_strcmp(name, "unset"))
		return (1);
	if (!ft_strcmp(name, "cd"))
		return (1);
	if (!ft_strcmp(name, "exit"))
		return (1);
	return (0);
}

static void	run_builtin_in_child(t_cmds *cmd, t_envp **env)
{
	t_envp	*tmp_env;
	int		status;

	if (!is_env_modifying_builtin(cmd->argv[0]))
		exit(exec_builtin(&cmd, env, 0));
	tmp_env = clone_env_list(*env);
	if (!tmp_env)
		exit(1);
	status = exec_builtin(&cmd, &tmp_env, 0);
	free_envp_list(&tmp_env);
	exit(status);
}

static void	setup_pipe_input(int prev_fd)
{
	if (prev_fd == STDIN_FILENO)
		return ;
	if (dup2(prev_fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(prev_fd);
}

static void	setup_pipe_output(t_cmds *cmd, int fd[2])
{
	if (!cmd->next)
		return ;
	if (dup2(fd[1], STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd[0]);
	close(fd[1]);
}

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

static int	create_child(t_cmds *cmd, t_envp **env, int prev_fd, int fd[2])
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

static void	update_parent_fds(t_cmds *cmd, int *prev_fd, int fd[2])
{
	if (*prev_fd != STDIN_FILENO)
		close(*prev_fd);
	if (!cmd->next)
		return ;
	close(fd[1]);
	*prev_fd = fd[0];
}

static void	update_status_from_wait(pid_t pid, pid_t last_pid,
	int status, int *last_status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGPIPE)
		write(2, " Broken pipe\n", 13);
	if (pid != last_pid)
		return ;
	if (WIFEXITED(status))
		*last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*last_status = 128 + WTERMSIG(status);
}

static int	wait_all_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		last_status;

	last_status = 1;
	while ((pid = wait(&status)) > 0)
		update_status_from_wait(pid, last_pid, status, &last_status);
	return (last_status);
}

int	execute_non_single(t_cmds *cmd, t_envp **env)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;

	prev_fd = STDIN_FILENO;
	last_pid = -1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) < 0)
			return (perror("pipe"), 1);
		pid = create_child(cmd, env, prev_fd, fd);
		if (pid < 0)
			return (1);
		update_parent_fds(cmd, &prev_fd, fd);
		last_pid = pid;
		cmd = cmd->next;
	}
	return (wait_all_children(last_pid));
}
