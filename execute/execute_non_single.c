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
		{
			free_envp_list(&head);
			return (NULL);
		}
		new_node->key = ft_strdup(env->key);
		if (env->value)
			new_node->value = ft_strdup(env->value);
		else
			new_node->value = NULL;
		new_node->next = NULL;
		if (!new_node->key || (env->value && !new_node->value))
		{
			free(new_node->key);
			free(new_node->value);
			free(new_node);
			free_envp_list(&head);
			return (NULL);
		}
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

	if (is_env_modifying_builtin(cmd->argv[0]))
	{
		tmp_env = clone_env_list(*env);
		if (!tmp_env)
			exit(1);
		status = exec_builtin(&cmd, &tmp_env, 0);
		free_envp_list(&tmp_env);
		exit(status);
	}
	exit(exec_builtin(&cmd, env, 0));
}

static void	child_process(t_cmds *cmd, t_envp **env, int prev_fd, int fd[2])
{
	if (prev_fd != STDIN_FILENO)
	{
		if (dup2(prev_fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (cmd->next)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
	}
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	if (cmd->next)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if (redirections(cmd) < 0)
		exit(1);
	if (cmd->argv && cmd->argv[0] && is_builtin(cmd->argv[0]))
		run_builtin_in_child(cmd, env);
	if (!cmd->argv || !cmd->argv[0])
		exit(0);
	exec_external(cmd, *env);
	exit(1);
}

int	execute_non_single(t_cmds *cmd, t_envp **env)
{
	int		fd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;
	int		status;
	int		last_status;

	prev_fd = STDIN_FILENO;
	last_pid = -1;
	last_status = 1;
	while (cmd)
	{
		if (cmd->next && pipe(fd) < 0)
		{
			perror("pipe");
			return (1);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return (1);
		}
		else if (pid == 0)
			child_process(cmd, env, prev_fd, fd);
		if (prev_fd != STDIN_FILENO)
			close(prev_fd);
		if (cmd->next)
		{
			close(fd[1]);
			prev_fd = fd[0];
		}
		last_pid = pid;
		cmd = cmd->next;
	}
	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
	}
	return (last_status);
}